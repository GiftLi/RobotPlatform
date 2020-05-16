#include "HR_EleBoxV2.h"


EleBoxV2::EleBoxV2(bool bErrorRecovryLINK,int nSlave,const char *device, int baud, char parity,int data_bit, int stop_bit):
HR_ElectricBoxHAL(bErrorRecovryLINK,nSlave,device, baud, parity,data_bit, stop_bit)
{
    m_nVerMajor=2;

}

EleBoxV2::~EleBoxV2()
{

}
int EleBoxV2::Sync()
{
    /* 申请内存空间 */
	uint16_t pTmpBuf[en_V2_Cnt] = {0};

    /* 读取寄存器数�? */
    if(0 != Read_holding_registers(REGISTER_START_ADDR, en_V2_Cnt,pTmpBuf))
	{
		printf("Read register error in BoxHansV4\n");

		return -1;
    }

	/* 更新结构体信�? */
	HandleSTData(pTmpBuf);
	
    return 0;
}

int EleBoxV2::HandleSTData(const uint16_t* pBuf)
{
	AutoSaftMutex stSyncLock(&m_ElectricBoxInfoLock);
	
	m_ElectricBoxInfo.nVerYear = 0;
    m_ElectricBoxInfo.nVerDate = 0;
    m_ElectricBoxInfo.nEmergencyStop = (pBuf[en_V2_EStopFUZHU] == 0x08);
    m_ElectricBoxInfo.nSafetyGuardStop = 0;  //4代电箱无安全光幕

	/* 还没有做转化 */
    m_ElectricBoxInfo.nResetSignal_EmergencyStop = pBuf[en_V2_EStopResetStatus];
    m_ElectricBoxInfo.nResetSignal_SafetyGuardStop = (pBuf[en_V2_ProStopReset]&0x02) >> 1; 
	
    m_ElectricBoxInfo.nRemoteSignal = (pBuf[en_V2_DC12VFlg] == 0x00);
    m_ElectricBoxInfo.nThreeStageSwitch_Signal = (pBuf[en_V2_ThreeEnableSwitch] == 0);

	for(int nIndex = 0; nIndex < ElectricIO; nIndex++)
	{
        m_ElectricBoxInfo.nDI[nIndex] = ( (pBuf[en_V2_RetDI]>>nIndex) & 1 ) == 0;
        m_ElectricBoxInfo.nDO[nIndex] = (pBuf[en_V2_RetDO]>>nIndex) & 1;
        m_ElectricBoxInfo.nSI[nIndex] = ( (pBuf[en_V2_RetCI]>>nIndex) & 1 ) == 0;
        m_ElectricBoxInfo.nSO[nIndex] = (pBuf[en_V2_RetCO]>>nIndex) & 1;
    }
    
    m_ElectricBoxInfo.nAnalogIN[enAnalogCh1] = (pBuf[en_V2_AnalogInput1] - 2048.0)/163.84;
	m_ElectricBoxInfo.nAnalogIN[enAnalogCh2] = (pBuf[en_V2_AnalogInput2] - 2048.0)/163.84;

    m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh1] = pBuf[en_V2_RetAnalogOutMode] & 0x03;
    m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh2] = (pBuf[en_V2_RetAnalogOutMode]>>2) & 0x03;

	/* 取决与当前的模拟模式 */
//    printf("reg act val =%d\n",pBuf[en_V2_RetCh1AnalogOutVal]);
    if(enAnalogMode_Voltag == m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh1]){
        m_ElectricBoxInfo.dbAnalogOut[enAnalogCh1] = pBuf[en_V2_RetCh1AnalogOutVal]*10.0/65535;
    }else if(enAnalogMode_Current == m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh1]){
        m_ElectricBoxInfo.dbAnalogOut[enAnalogCh1] = pBuf[en_V2_RetCh1AnalogOutVal]*16.0/65535 + 4;
    }else {
         m_ElectricBoxInfo.dbAnalogOut[enAnalogCh1] = 0;
    }

    if(enAnalogMode_Voltag == m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh2]){
        m_ElectricBoxInfo.dbAnalogOut[enAnalogCh2] = pBuf[en_V2_RetCh2AnalogOutVal]*10.0/65535;
    }else if(enAnalogMode_Current == m_ElectricBoxInfo.nAnalogOutMode[enAnalogCh2]){
		m_ElectricBoxInfo.dbAnalogOut[enAnalogCh2] = pBuf[en_V2_RetCh2AnalogOutVal]*16.0/65535 + 4;
    }else {
        m_ElectricBoxInfo.dbAnalogOut[enAnalogCh2] = 0;
   }
    
    m_ElectricBoxInfo.db12V_Voltag = pBuf[en_V2_12vVol] * 0.00642;
    m_ElectricBoxInfo.db12V_Current = pBuf[en_V2_12vCur] * 0.00197;
    m_ElectricBoxInfo.db24V_Voltag = pBuf[en_V2_24vVol] * 0.01343;
    m_ElectricBoxInfo.db24V_Current = pBuf[en_V2_24vCur] * 0.00197;
    m_ElectricBoxInfo.db48VIN_Voltag = pBuf[en_V2_48vInputVol] * 0.02719;
    m_ElectricBoxInfo.db48VIN_Current = 0;
    m_ElectricBoxInfo.db48VOUT_Voltag = pBuf[en_V2_Rbt48vVol] * 0.02563;
    m_ElectricBoxInfo.db48VOUT_Current = (pBuf[en_V2_Rbt48vCur1] * 0.01831 - 37.5)
										  + (pBuf[en_V2_Rbt48vCur2] * 0.01831 - 37.5);
	
	return 0;
	
}


bool EleBoxV2::TestConnect()
{
    uint16_t dest=0;
    return Read_holding_registers(1,1,&dest)==0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EleBoxV2::Electrify48VOUT()
{
	__useconds_t ms_10 = 10 * 1000;
    /* 设置寄存�? */
    if(Write_holding_register(en_V2_ControlWord, 0x60) != 0)
	{
		return -1;
	}

	usleep(ms_10);

    if(Write_holding_register(en_V2_ControlWord, 0x62) != 0)
	{
		return -1;
	}

	usleep(ms_10);

    if(Write_holding_register(en_V2_ControlWord, 0x66) != 0)
	{
		return -1;
	}

	usleep(ms_10);

    if(Write_holding_register(en_V2_ControlWord, 0x64) != 0)
	{
		return -1;
	}

	usleep(ms_10);

    if(Write_holding_register(en_V2_ControlWord, 0x6c) != 0)
	{
		return -1;
	}
	
	/* �?测是否设置成�? */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)
	{
		double dbVoltag = 0;
		double dbCurrent = 0;
		
		ReadPowerSupply_48VOUT(dbVoltag,dbCurrent);//48V OUT

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
int EleBoxV2::Blackout48VOUT()
{
	__useconds_t ms_10 = 10 * 1000;
	
    if(Write_holding_register(en_V2_ControlWord, 0x68) != 0)
	{
		return -1;
	}

	usleep(ms_10);

    if(Write_holding_register(en_V2_ControlWord, 0x00) != 0)
	{
		return -1;
	}

	/* �?测是否设置成�? */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)  // 是否�?50ms的超时时间，要待测试
	{
		double dbVoltag = 0;
		double dbCurrent = 0;
		
		ReadPowerSupply_48VOUT(dbVoltag,dbCurrent);//48V OUT

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

int EleBoxV2::ResetEmergencyStop()
{
	__useconds_t ms_10 = 10 * 1000;
	
    if(Write_holding_register(en_V2_ControlWord, 0x60) != 0)
	{
		return -1;
	}

	usleep(ms_10);
	
	if(Write_holding_register(en_V2_ResetEStop, 0) != 0)
	{
		return -1;
	}

	usleep(ms_10);

	
	if(Write_holding_register(en_V2_ControlWord, 1) != 0)
	{
		return -1;
	}

	/* �?测是否设置成�? */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt++)  // 是否�?50ms的超时时间，要待测试
	{
		if(!IsEmergencyStop())
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

int EleBoxV2::ResetSafetyGuradStop()
{
    return 0;
}

int EleBoxV2::SetAnalogOUT_Mode(int nIndex,int nAnalogMode)
{
    if(nAnalogMode != enAnalogMode_Voltag
        && nAnalogMode != enAnalogMode_Current)
	{
		printf("Invaild Param: [nAnalogMode = %d] in set Analog output mode\n",nAnalogMode);
		return -1;
    }

    if(enAnalogCh1 != nIndex
            && enAnalogCh2 != nIndex)
    {
        printf("Invaild Param: [nIndex = %d] in set Analog output mode\n",nIndex);
        return -1;
    }

	uint16_t curMode = 0;
	if(0 != Read_holding_registers(en_V2_AnalogOutMode, 1, &curMode))
	{
        printf("read AnalogMode register error in SetAnalogOUT_Mode\n");

		return -1;
	}

	int nZore = 0;

    nZore = ( enAnalogCh1 == nIndex) ? (curMode | 0x03) : (curMode | 0x0c);
	

	if(Write_holding_register(en_V2_AnalogOutMode, nZore) != 0)  /*清零*/
	{
        printf("Set AnalogMode register error in  init SetAnalogOUT_Mode\n");
		return -1;
	}

	int nSetMode = 0;

    /* ch1 or ch2*/
    if(enAnalogCh1 == nIndex)
    {
        nSetMode = (nAnalogMode == enAnalogMode_Voltag) ? (~(1<<1)&nZore) : (~1&nZore);
    }
    else {
        nSetMode = (nAnalogMode == enAnalogMode_Voltag) ? ( (~(1<<3)) & nZore ) : ( (~(1<<2)) & nZore);
    }

    if(Write_holding_register(en_V2_AnalogOutMode, nSetMode) != 0)  /*设置*/
	{
        printf("Set AnalogMode register error in SetAnalogOUT_Mode\n");
		return -1;
	}
	
	/* �?测是否设置成�? */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)  // 是否�?50ms的超时时间，要待测试
	{
		int nMode;
		double dbAnalogOUT;
        ReadAnalogOUT(nIndex,nMode,dbAnalogOUT);
		
		if(nMode == nAnalogMode)
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);

		nCnt++;
	}

	if(!flg)
	{
        printf("timeout error in SetAnalogOUT_Mode\n");
		return -1;
	}

    return 0;
}
int EleBoxV2::SetAnalogOUT_Value(int nIndex,double dbAnalogOUT)
{
    int nRegisterAddr = 0;
	
	switch(nIndex)
	{
		case enAnalogCh1:
			nRegisterAddr = en_V2_Ch1AnalogOutVal;		
			break;

		case enAnalogCh2:
			nRegisterAddr = en_V2_Ch2AnalogOutVal;
			break;

		default:
			printf("Invaild Param: [index = %d] in set Analog output mode\n",nIndex);
			return -1;
	}

	/* 获取当前的模拟输出模�? */
	int nMode;
	double dbCurOUT;
	ReadAnalogOUT(nIndex,nMode,dbCurOUT);

	/* 确定设置寄存器�?? */
	int nSetVal = 0;
	if(enAnalogMode_Voltag == nMode
		&& (dbAnalogOUT >= 0.0 && dbAnalogOUT <= 10.0))
	{
		nSetVal = dbAnalogOUT * 65535 / 10;
	}
	else if(dbAnalogOUT >= 4.0 && dbAnalogOUT <= 20.0)
	{
		nSetVal = (dbAnalogOUT - 4) * 65535 / 16;
	}
	else
	{
        printf("SystemBoard error! [cur mode = %d] [SetVal=%f]in set Analog output val\n",nMode,dbAnalogOUT);
		return -1;
	}
	
    if(Write_holding_register(nRegisterAddr, nSetVal) != 0)
	{
        printf("write register error on SetAnalogOUT_Val\n");
		return -1;
	}

	/* �?测是否设置成�? */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)  // 是否�?50ms的超时时间，要待测试
	{
		int nMode;
		double dbCurOUT;
		ReadAnalogOUT(nIndex,nMode,dbCurOUT);
		
		if((dbCurOUT > (dbAnalogOUT -1)) 
			&& (dbCurOUT < (dbAnalogOUT +1)))
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);

		nCnt++;
	}

	if(!flg)
	{
        printf("timeout error in SetAnalogOUT_Val\n");
		return -1;
	}
	
    return 0;
}
int EleBoxV2::SetDO(int nIndex,int nVal)
{
    /* 获取当前的IO状�?? */
	uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7)
		|| (nVal < 0 || nVal > 1) )
	{
		printf("Set DO Param error in SetDO\n");
		return -1;
	}

    if(0 != Read_holding_registers(en_V2_RetDO, 1, &pTmpBuf))
	{
		printf("Read DO register error in SetDO\n");

		return -1;
	}
	
	/* 确定设置�? */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
    if(Write_holding_register(en_V2_DO, pTmpBuf) != 0)
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
		
		ReadDO(nDOStatus[0],nDOStatus[1],nDOStatus[2],nDOStatus[3],nDOStatus[4],nDOStatus[5],nDOStatus[6],nDOStatus[7]);

		if(nDOStatus[nIndex] == nVal )
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);
	}

	if(!flg)
	{
        printf("timeout error in SetAnalogOUT_Mode\n");
		return -1;
	}
	
    return 0;
}
int EleBoxV2::SetSO(int nIndex,int nVal)
{
    uint16_t pTmpBuf = 0;

	if((nIndex < 0 || nIndex > 7) || (nVal < 0 || nVal > 1) )
	{
		printf("Set CO Param error in SetCO\n");
		return -1;
	}

	/* 获取当前的IO状�?? */
    if(0 != Read_holding_registers(en_V2_RetCO, 1, &pTmpBuf))
	{
		printf("Read CO register error in SetDO\n");

		return -1;
	}
	
	/* 确定设置�? */
	if(1 == nVal)
	{
		pTmpBuf = (1 << nIndex) | (pTmpBuf);
	}
	else
	{
		pTmpBuf = (~(1 << nIndex)) & (pTmpBuf);
	}

	/* 写寄存器 */
    if(Write_holding_register(en_V2_CO, pTmpBuf) != 0)
	{
		return -1;
	}

	/* 判断是否设置成功 */
	int nCnt = 0;
	bool flg = false;
	
	while(5 != nCnt)
	{
		int nCOStatus[8] = {0};
		
		ReadSO(nCOStatus[0],nCOStatus[1],nCOStatus[2],nCOStatus[3],nCOStatus[4],nCOStatus[5],nCOStatus[6],nCOStatus[7]);

		if(nCOStatus[nIndex] == nVal )
		{
			flg = true;
			break;
		}

		usleep(10 * 1000);

		nCnt++;
	}

	if(!flg)
	{
		return -1;
	}
	
    return 0;
}
