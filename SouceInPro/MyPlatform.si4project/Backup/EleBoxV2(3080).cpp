#include "EleBoxV2.h"

bool EleBoxV2::syncBuf(void)
{
	/* 申请内存空间 */
	uint16_t pTmpBuf[en_V2_Cnt] = {0};


	/* 读取寄存器数据 */
	if(readHoldingRegister(REGISTER_START_ADDR, en_V2_Cnt,pTmpBuf) < 0)
	{
		printf("Read register error in BoxHansV2\n");

		return false;
	}

	/* 更新结构体信息 */
	handleSTBuf(pTmpBuf);
	
    return true;
}

bool EleBoxV2::handleSTBuf(uint16_t* pBuf)
{
	AutoSaftMutex stSyncLock(&m_lBufLock);
	
	m_stBufInfo.nVerYear = 0;
    m_stBufInfo.nVerDate = 0;
    m_stBufInfo.nEmergencyStop = (pBuf[en_V2_EStopFUZHU] == 0x08);
    m_stBufInfo.nSafetyGuardStop = 0;  //4代电箱无安全光幕

	/* 还没有做转化 */
    m_stBufInfo.nResetSignal_EmergencyStop = pBuf[en_V2_EStopResetStatus];
    m_stBufInfo.nResetSignal_SafetyGuardStop = (pBuf[en_V2_ProStopReset]&0x02) >> 1; 
	
    m_stBufInfo.nRemoteSignal = (pBuf[en_V2_DC12VFlg] == 0x00);
    m_stBufInfo.nThreeStageSwitch_Signal = (pBuf[en_V2_ThreeEnableSwitch] == 0);

	for(int nIndex = 0; nIndex < en_IO_Number; nIndex++)
	{
        m_stBufInfo.nDI[nIndex] = ( (pBuf[en_V2_RetDI]>>nIndex) & 1 ) == 0;
        m_stBufInfo.nDO[nIndex] = (pBuf[en_V2_RetDO]>>nIndex) & 1;
        m_stBufInfo.nSI[nIndex] = ( (pBuf[en_V2_RetCI]>>nIndex) & 1 ) == 0;
        m_stBufInfo.nSO[nIndex] = (pBuf[en_V2_RetCO]>>nIndex) & 1;
    }
    
    m_stBufInfo.nAnalogIN[en_AnalogIO_CH1] = (pBuf[en_V2_AnalogInput1] - 2048.0)/163.84;
	m_stBufInfo.nAnalogIN[en_AnalogIO_CH2] = (pBuf[en_V2_AnalogInput2] - 2048.0)/163.84;

    m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1] = pBuf[en_V2_RetAnalogOutMode] & 0x03;
    m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1] = (pBuf[en_V2_RetAnalogOutMode]>>2) & 0x03;

	/* 取决与当前的模拟模式 */
    if(en_AnalogIO_Mode_Vol == m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1]){
        m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V2_RetCh1AnalogOutVal]*10.0/65535;
    }else if(en_AnalogIO_Mode_Cur == m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1]){
        m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V2_RetCh1AnalogOutVal]*16.0/65535 + 4;
    }else {
         m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = 0;
    }

    if(en_AnalogIO_Mode_Vol == m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH2]){
        m_stBufInfo.dbAnalogOut[en_AnalogIO_CH2] = pBuf[en_V2_RetCh2AnalogOutVal]*10.0/65535;
    }else if(en_AnalogIO_Mode_Cur == m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH2]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH2] = pBuf[en_V2_RetCh2AnalogOutVal]*16.0/65535 + 4;
    }else {
        m_stBufInfo.dbAnalogOut[en_AnalogIO_CH2] = 0;
   }
    
    m_stBufInfo.db12V_Voltag = pBuf[en_V2_12vVol] * 0.00642;
    m_stBufInfo.db12V_Current = pBuf[en_V2_12vCur] * 0.00197;
    m_stBufInfo.db24V_Voltag = pBuf[en_V2_24vVol] * 0.01343;
    m_stBufInfo.db24V_Current = pBuf[en_V2_24vCur] * 0.00197;
    m_stBufInfo.db48VIN_Voltag = pBuf[en_V2_48vInputVol] * 0.02719;
    m_stBufInfo.db48VIN_Current = 0;
    m_stBufInfo.db48VOUT_Voltag = pBuf[en_V2_Rbt48vVol] * 0.02563;
    m_stBufInfo.db48VOUT_Current = (pBuf[en_V2_Rbt48vCur1] * 0.01831 - 37.5)
										  + (pBuf[en_V2_Rbt48vCur2] * 0.01831 - 37.5);

	return true;
}


int EleBoxV2::electrify48vOut(void)
{
	__useconds_t ms_10 = 10 * 1000;
	
    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x60))
	{
		return -1;
	}

	usleep(ms_10);

    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x62))
	{
		return -1;
	}

	usleep(ms_10);

    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x66))
	{
		return -1;
	}

	usleep(ms_10);

    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x64))
	{
		return -1;
	}

	usleep(ms_10);

    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x6c))
	{
		return -1;
	}
	
	/* 棿测是否设置成势 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)
	{
		double dbVoltag = 0;
		double dbCurrent = 0;
		
		readPower_48vOutput(dbVoltag,dbCurrent);//48V OUT

		if(dbVoltag > 47.0
			&& dbVoltag < 49.0)
		{
			flg = true;
			break;
		}

		usleep(ms_10);
	}

	if(!flg)
	{
		return -1;
	}
	
    return 0;

}

int EleBoxV2::blackout48vOut(void)
{
	__useconds_t ms_10 = 10 * 1000;
	
    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x68))
	{
		return -1;
	}

	usleep(ms_10);

    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x00))
	{
		return -1;
	}

	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt) 
	{
		double dbVoltag = 0;
		double dbCurrent = 0;
		
		readPower_48vOutput(dbVoltag,dbCurrent);//48V OUT

		if(dbVoltag < 5.0 )
		{
			flg = true;
			break;
		}

		usleep(ms_10);

		nCnt++;
	}

	if(!flg)
	{
		return -1;
	}
	
    return 0;
}

int EleBoxV2::resetEStop()
{
	__useconds_t ms_10 = 10 * 1000;
	
    if(0 > writeHoldingRegister(en_V2_ControlWord, 0x60))
	{
		return -1;
	}

	usleep(ms_10);
	
	if(0 > writeHoldingRegister(en_V2_ResetEStop, 0))
	{
		return -1;
	}

	usleep(ms_10);

	
	if(0 > writeHoldingRegister(en_V2_ControlWord, 1))
	{
		return -1;
	}

	/* 棿测是否设置成势 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)  // 是否丿50ms的超时时间，要待测试
	{
		if(!isEStop())
		{
			flg = true;
			break;
		}

		usleep(ms_10);
	}

	if(!flg)
	{
		return -1;
	}

    return 0;
}


int EleBoxV2::resetSafetyGuradStop(void)
{
	return 0;
}

int EleBoxV2::setAnalogOutputMode(const int& nIndex, const int& nMode)
{
	if(nMode != en_AnalogIO_Mode_Vol
        && nMode != en_AnalogIO_Mode_Cur)
	{
		printf("Invaild Param: [nAnalogMode = %d] in set Analog output mode\n",nMode);
		return -1;
    }

    if(en_AnalogIO_CH1 != nIndex
            && en_AnalogIO_CH2 != nIndex)
    {
        printf("Invaild Param: [nIndex = %d] in set Analog output mode\n",nIndex);
        return -1;
    }

	uint16_t curMode = 0;
	if(0 != readHoldingRegister(en_V2_AnalogOutMode, 1, &curMode))
	{
        printf("read AnalogMode register error in setAnalogOutputMode\n");

		return -1;
	}

	int nZore = 0;

    nZore = ( en_AnalogIO_CH1 == nIndex) ? (curMode | 0x03) : (curMode | 0x0c);
	

	if(writeHoldingRegister(en_V2_AnalogOutMode, nZore) != 0)  /*清零*/
	{
        printf("Set AnalogMode register error in  init setAnalogOutputMode\n");
		return -1;
	}

	int nSetMode = 0;

    /* ch1 or ch2*/
    if(en_AnalogIO_CH1 == nIndex)
    {
        nSetMode = (nMode == en_AnalogIO_Mode_Vol) ? (~(1<<1)&nZore) : (~1&nZore);
    }
    else {
        nSetMode = (nMode == en_AnalogIO_Mode_Vol) ? ( (~(1<<3)) & nZore ) : ( (~(1<<2)) & nZore);
    }

    if(writeHoldingRegister(en_V2_AnalogOutMode, nSetMode) != 0)  /*设置*/
	{
        printf("Set AnalogMode register error in setAnalogOutputMode\n");
		return -1;
	}
	
	/* 棿测是否设置成势 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)  // 是否丿50ms的超时时间，要待测试
	{
		int nCurMode;
        readAnalogOutputMode(nIndex,nCurMode);
		
		if(nCurMode == nMode)
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);

		nCnt++;
	}

	if(!flg)
	{
        printf("timeout error in setAnalogOutputMode\n");
		return -1;
	}

    return 0;
}
int EleBoxV2::setAnalogOutputValue(const int& nIndex, const double& dVal)
{
	int nRegisterAddr = 0;
	
	switch(nIndex)
	{
		case en_AnalogIO_CH1:
			nRegisterAddr = en_V2_Ch1AnalogOutVal;		
			break;

		case en_AnalogIO_CH2:
			nRegisterAddr = en_V2_Ch2AnalogOutVal;
			break;

		default:
			printf("Invaild Param: [index = %d] in set Analog output mode\n",nIndex);
			return -1;
	}

	/* 获取当前的模拟输出模弿 */
	int nCurMode;
    readAnalogOutputMode(nIndex,nCurMode);

	/* 确定设置寄存器忿 */
	int nSetVal = 0;
	if(en_AnalogIO_Mode_Vol == nCurMode
		&& (dVal >= 0.0 && dVal <= 10.0))
	{
		nSetVal = dVal * 65535 / 10;
	}
	else if(dVal >= 4.0 && dVal <= 20.0)
	{
		nSetVal = (dVal - 4) * 65535 / 16;
	}
	else
	{
        printf("SystemBoard error! [cur mode = %d] [SetVal=%f]in set Analog output val\n",nCurMode,nSetVal);
		return -1;
	}
	
    if(writeHoldingRegister(nRegisterAddr, nSetVal) != 0)
	{
        printf("write register error on setAnalogOutputValue\n");
		return -1;
	}

	/* 棿测是否设置成势 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)  // 是否丿50ms的超时时间，要待测试
	{
		double dbCurOUT;
		readAnalogOutput(nIndex,dbCurOUT);
		
		if((dbCurOUT > (dVal -1)) 
			&& (dbCurOUT < (dVal +1)))
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);

		nCnt++;
	}

	if(!flg)
	{
        printf("timeout error in setAnalogOutputValue\n");
		return -1;
	}
	
    return 0;
}

int EleBoxV2::setDO(const int& nIndex,const int& nVal)
{
	uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7)
		|| (nVal < 0 || nVal > 1) )
	{
		printf("Set DO Param error in SetDO\n");
		return -1;
	}

    if(0 != readHoldingRegister(en_V2_RetDO, 1, &pTmpBuf))
	{
		printf("Read DO register error in SetDO\n");

		return -1;
	}
	
	/* 确定设置倿 */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
    if(writeHoldingRegister(en_V2_DO, pTmpBuf) != 0)
	{
        printf("Write DO register error in SetDO\n");
		return -1;
	}

	/* 判断是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)
	{
		int nDOStatus[8] = {0};
		
		readDO(nDOStatus[0],nDOStatus[1],nDOStatus[2],nDOStatus[3],nDOStatus[4],nDOStatus[5],nDOStatus[6],nDOStatus[7]);

		if(nDOStatus[nIndex] == nVal )
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
        printf("timeout error in SetDO\n");
		return -1;
	}
	
    return 0;
}

int EleBoxV2::setCO(const int& nIndex,const int& nVal)
{
	uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7)
		|| (nVal < 0 || nVal > 1) )
	{
		printf("Set CO Param error in setCO\n");
		return -1;
	}

    if(0 != readHoldingRegister(en_V2_RetCO, 1, &pTmpBuf))
	{
		printf("Read CO register error in setCO\n");

		return -1;
	}
	
	/* 确定设置倿 */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
    if(writeHoldingRegister(en_V2_CO, pTmpBuf) != 0)
	{
        printf("Write CO register error in setCO\n");
		return -1;
	}

	/* 判断是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)
	{
		int nCOStatus[8] = {0};
		
		readCO(nCOStatus[0],nCOStatus[1],nCOStatus[2],nCOStatus[3],nCOStatus[4],nCOStatus[5],nCOStatus[6],nCOStatus[7]);

		if(nCOStatus[nIndex] == nVal )
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
        printf("timeout error in SetCO\n");
		return -1;
	}
	
    return 0;
}









