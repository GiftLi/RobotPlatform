#include "EleBoxV4.h"

bool EleBoxV4::syncBuf(void)
{
	/* 申请内存空间 */
	uint16_t pTmpBuf[en_V4_Cnt] = {0};


	/* 读取寄存器数据 */
	if(readHoldingRegister(en_V4_StartAddr, en_V4_Cnt,pTmpBuf) < 0)
	{
		printf("Read register error in BoxHansV4\n");

		return -1;
	}

	/* 更新结构体信息 */
	handleSTBuf(pTmpBuf);
	
    return 0;
}

bool EleBoxV4::handleSTBuf(uint16_t* pBuf)
{
	AutoSaftMutex stSyncLock(&m_lBufLock);
	
	m_stBufInfo.nVerYear = pBuf[en_V4_McsVerYear];
    m_stBufInfo.nVerDate = pBuf[en_V4_McsVerDate];
    m_stBufInfo.nEmergencyStop = (pBuf[en_V4_EStopFlg] == 0x10);
    m_stBufInfo.nSafetyGuardStop = 0;  //4代电箱无安全光幕

	/* 还没有做转化 */
    m_stBufInfo.nResetSignal_EmergencyStop = pBuf[en_V4_ProStopInputFlg];
    m_stBufInfo.nResetSignal_SafetyGuardStop = pBuf[en_V4_ProStopInputFlg];
	
    m_stBufInfo.nRemoteSignal = (pBuf[en_V4_DC12vPoweroffFlg] == 0x00);
    m_stBufInfo.nThreeStageSwitch_Signal = (pBuf[en_V4_EnableSwitch] == 0);

	for(int nIndex = 0; nIndex < en_IO_Number; nIndex++)
	{
		m_stBufInfo.nDI[nIndex] = (pBuf[en_V4_DI]>>nIndex) & 1;
    	m_stBufInfo.nDO[nIndex] = (pBuf[en_V4_RetDO]>>nIndex) & 1;
    	m_stBufInfo.nSI[nIndex] = (pBuf[en_V4_CI]>>nIndex) & 1;
    	m_stBufInfo.nSO[nIndex] = (pBuf[en_V4_RetCO]>>nIndex) & 1;
	}
    
    m_stBufInfo.nAnalogIN[en_AnalogIO_CH1] = (pBuf[en_V4_AnalogInput1] - 2048.0)/163.84;
	m_stBufInfo.nAnalogIN[en_AnalogIO_CH2] = (pBuf[en_V4_AnalogInput2] - 2048.0)/163.84;

	m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1] = pBuf[en_V4_RetCh1AnalogOutMode];
	m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH2] = pBuf[en_V4_RetCh2AnalogOutMode];

	/* 取决与当前的模拟模式 */
	if(en_AnalogIO_Mode_Vol == pBuf[en_V4_RetCh1AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V4_RetCh1AnalogOutVal]*10.0/65535;
	}else if(en_AnalogIO_Mode_Cur == pBuf[en_V4_RetCh1AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH2] = pBuf[en_V4_RetCh1AnalogOutVal]*16.0/65535 + 4;
	}

	if(en_AnalogIO_Mode_Vol == pBuf[en_V4_RetCh2AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V4_RetCh2AnalogOutVal]*10.0/65535;
	}else if(en_AnalogIO_Mode_Cur == pBuf[en_V4_RetCh2AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH2] = pBuf[en_V4_RetCh2AnalogOutVal]*16.0/65535 + 4;
	}
    
    m_stBufInfo.db12V_Voltag = pBuf[en_V4_12vVol] * 0.00642;
    m_stBufInfo.db12V_Current = pBuf[en_V4_12vCur] * 0.00197;
    m_stBufInfo.db24V_Voltag = pBuf[en_V4_24vVol] * 0.01343;
    m_stBufInfo.db24V_Current = pBuf[en_V4_24vCur] * 0.00197;
    m_stBufInfo.db48VIN_Voltag = pBuf[en_V4_48vInputVol] * 0.02719;
    m_stBufInfo.db48VIN_Current = 0;
    m_stBufInfo.db48VOUT_Voltag = pBuf[en_V4_Rbt48vVol] * 0.02563;
    m_stBufInfo.db48VOUT_Current = (pBuf[en_V4_Rbt48vCur1] * 0.01831 - 37.5)
										  + (pBuf[en_V4_Rbt48vCur2] * 0.01831 - 37.5);

	return true;
}


int EleBoxV4::electrify48vOut(void)
{
	/* 设置寄存器 */
	if(writeHoldingRegister(en_V4_ControlWord, 1) < 0)
	{
		return -1;
	}
	
	/* 检测是否设置成功 */
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

		usleep(10 * 1000);
	}

	if(!flg)
	{
		return -1;
	}
	
	return 0;

}

int EleBoxV4::blackout48vOut(void)
{
	/* 设置寄存器 */
	if(writeHoldingRegister(en_V4_ControlWord, 0) < 0)
	{
		return -1;
	}
	
	/* 检测是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)
	{
		double dbVoltag = 0;
		double dbCurrent = 0;
		
		readPower_48vOutput(dbVoltag,dbCurrent);//48V OUT

		if(dbVoltag < 5.0)
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
		return -1;
	}
	
	return 0;
}

int EleBoxV4::resetEStop(void)
{
	if(writeHoldingRegister(en_V4_ResetEStop, 0) < 0)
	{
		return -1;
	}

	usleep(100 * 1000);
	
	if(writeHoldingRegister(en_V4_ResetEStop, 1) < 0)
	{
		return -1;
	}

	/* 检测是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)  // 是否为50ms的超时时间，要待测试
	{
		if(!isEStop())
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
		return -1;
	}

    return 0;
}

int EleBoxV4::resetSafetyGuradStop(void)
{
	return 0;
}

int EleBoxV4::setAnalogOutputMode(const int& nIndex, const int& nMode)
{
	int nRegisterAddr = 0;
	
	switch(nIndex)
	{
		case en_AnalogIO_CH1:
			nRegisterAddr = en_V4_CH1AnalogOutMode;		
			break;

		case en_AnalogIO_CH2:
			nRegisterAddr = en_V4_CH2AnalogOutMode;
			break;

		default:
			printf("Invaild Param: [index = %d] in set Analog output mode\n",nIndex);
			return -1;
	}

	if(nMode != en_AnalogIO_Mode_Vol 
		&& nMode != en_AnalogIO_Mode_Vol)
	{
		printf("Invaild Param: [nAnalogMode = %d] in set Analog output mode\n",nMode);
		return -1;
	}
	
	if(writeHoldingRegister(nRegisterAddr, 0) < 0 /*清零*/
		||writeHoldingRegister(nRegisterAddr, nMode) < 0) /*设置*/
	{
		return -1;
	}

	/* 检测是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)  // 是否为50ms的超时时间，要待测试
	{
		int nCurMode;
		readAnalogOutputMode(nIndex,nCurMode);
		
		if(nCurMode == nMode)
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
		return -1;
	}

    return 0;
}
int EleBoxV4::setAnalogOutputValue(const int& nIndex, const double& dVal)
{
	int nRegisterAddr = 0;
	
	switch(nIndex)
	{
		case en_AnalogIO_CH1:
			nRegisterAddr = en_V4_CH1AnalogOutValue;		
			break;

		case en_AnalogIO_CH2:
			nRegisterAddr = en_V4_CH2AnalogOutValue;
			break;

		default:
			printf("Invaild Param: [index = %d] in set Analog output mode\n",nIndex);
			return -1;
	}

	/* 获取当前的模拟输出模式 */
	double dbCurOUT;
	readAnalogOutput(nIndex,dbCurOUT);
	int nCurMode;
	readAnalogOutputMode(nIndex,nCurMode);

	/* 确定设置寄存器值 */
	int nSetVal = 0;
	if(nCurMode == en_AnalogIO_Mode_Vol)
	{
		nSetVal = dbCurOUT * 65535 / 10;
	}
	else if(nCurMode == en_AnalogIO_Mode_Cur)
	{
		nSetVal = (dbCurOUT - 4) * 65535 / 16;
	}
	else
	{
		printf("SystemBoard error! [cur mode = %d]in set Analog output val\n",nCurMode);
		return -1;
	}

	if(writeHoldingRegister(nRegisterAddr, nSetVal) < 0)
	{
		return -1;
	}

	/* 检测是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)  // 是否为50ms的超时时间，要待测试
	{
		double dbCurOUT;
		readAnalogOutput(nIndex,dbCurOUT);
		
		if((dbCurOUT > (dbCurOUT -1)) 
			&& (dbCurOUT < (dbCurOUT +1)))
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
		return -1;
	}
	
    return 0;
}

int EleBoxV4::setDO(const int& nIndex,const int& nVal)
{
	/* 获取当前的IO状态 */
	uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7) || (nVal < 0 || nVal > 1) )
	{
		printf("Set DO Param error in SetDO\n");
		return -1;
	}

	if(readHoldingRegister(en_V4_RetDO, 1, &pTmpBuf) < 0)
	{
		printf("Read DO register error in SetDO\n");

		return -1;
	}
	
	/* 确定设置值 */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
	if(writeHoldingRegister(en_V4_DO, pTmpBuf) < 0)
	{
		return -1;
	}

	/* 判断是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)
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
		return -1;
	}
	
    return 0;
}

int EleBoxV4::setCO(const int& nIndex,const int& nVal)
{
	uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7) || (nVal < 0 || nVal > 1) )
	{
		printf("Set CO Param error in SetCO\n");
		return -1;
	}

	/* 获取当前的IO状态 */
	if(!readHoldingRegister(en_V4_RetCO, 1, &pTmpBuf))
	{
		printf("Read CO register error in SetDO\n");

		return -1;
	}
	
	/* 确定设置值 */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
	if(writeHoldingRegister(en_V4_CO, pTmpBuf) < 0)
	{
		return -1;
	}

	/* 判断是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)
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
		return -1;
	}
	
    return 0;
}


