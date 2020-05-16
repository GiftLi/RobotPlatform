#include "EleBoxV4.h"

bool EleBoxV4::syncBuf(void)
{
	/* 申请内存空间 */
	uint16_t pTmpBuf[en_V4_Cnt] = {0};


	/* 读取寄存器数据 */
	if(!readHoldingRegister(en_V4_StartAddr, en_V4_Cnt,pTmpBuf))
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
		m_stBufInfo.nDI[nIndex] = (pBuf[en_V4_DI]>>nIndex) && 1;
    	m_stBufInfo.nDO[nIndex] = (pBuf[en_V4_RetDO]>>nIndex) && 1;
    	m_stBufInfo.nSI[nIndex] = (pBuf[en_V4_CI]>>nIndex) && 1;
    	m_stBufInfo.nSO[nIndex] = (pBuf[en_V4_RetCO]>>nIndex) && 1;
	}
    
    m_stBufInfo.nAnalogIN[en_AnalogIO_CH1] = (pBuf[en_V4_AnalogInput1] - 2048.0)/163.84;
	m_stBufInfo.nAnalogIN[en_AnalogIO_CH2] = (pBuf[en_V4_AnalogInput2] - 2048.0)/163.84;

	m_stBufInfo.nAnalogOutMode[en_AnalogIO_CH1] = pBuf[en_V4_RetCh1AnalogOutMode];
	m_stBufInfo.nAnalogOutMode[[en_AnalogIO_CH2]] = pBuf[en_V4_RetCh2AnalogOutMode];

	/* 取决与当前的模拟模式 */
	if(en_AnalogIO_Mode_Vol == pBuf[en_V4_RetCh1AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V4_RetCh1AnalogOutVal]*10.0/65535;
	}else if(en_AnalogIO_Mode_Cur == pBuf[en_V4_RetCh1AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[[en_AnalogIO_CH2]] = pBuf[en_V4_RetCh1AnalogOutVal]*16.0/65535 + 4;
	}

	if(en_AnalogIO_Mode_Vol == pBuf[en_V4_RetCh2AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[en_AnalogIO_CH1] = pBuf[en_V4_RetCh2AnalogOutVal]*10.0/65535;
	}else if(en_AnalogIO_Mode_Cur == pBuf[en_V4_RetCh2AnalogOutMode]){
		m_stBufInfo.dbAnalogOut[[en_AnalogIO_CH2]] = pBuf[en_V4_RetCh2AnalogOutVal]*16.0/65535 + 4;
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
}

