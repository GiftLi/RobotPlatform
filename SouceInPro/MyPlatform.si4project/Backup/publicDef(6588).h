#ifndef __PUBLICDEF_H_
#define __PUBLICDEF_H_
#include <pthread.h>
#include <string.h>


typedef enum _EN_EleBox_Type
{
	en_EleBox_Type_V1=1,
	en_EleBox_Type_V2,
	en_EleBox_Type_V3,
	en_EleBox_Type_V4,
	en_EleBox_Type_Simulation,
	en_EleBox_Type_cnt
}EN_EleBox_Type;

typedef enum _EN_IO
{
	en_IO_0=0,
	en_IO_1,
	en_IO_2,
	en_IO_3,
	en_IO_4,
	en_IO_5,
	en_IO_6,
	en_IO_7,
	en_IO_Number
}EN_IO;

typedef enum _EN_AnalogIO
{
	en_AnalogIO_CH1=0,
	en_AnalogIO_CH2,
	en_AnalogIO_Number
}EN_AnalogIO;

typedef enum _EN_AnalogIO_Mode
{
	en_AnalogIO_Mode_Vol=1,
	en_AnalogIO_Mode_Cur,
	en_AnalogIO_Mode_Number
}EN_AnalogIO_Mode;

/*
 @ ElectricityBox all only read Info
*/
typedef struct _ST_EleBoxBuf
{
    /* data */
    int nVerYear;
    int nVerDate;
    int nEmergencyStop;
    int nSafetyGuardStop;
    int nResetSignal_EmergencyStop;
    int nResetSignal_SafetyGuardStop;
    int nRemoteSignal;
    int nThreeStageSwitch_Signal;
    int nDI[en_IO_Number];
    int nDO[en_IO_Number];
    int nSI[en_IO_Number];
    int nSO[en_IO_Number];
    
    int nAnalogIN[en_AnalogIO_Number];
    int nAnalogOutMode[en_AnalogIO_Mode_Number];
    double dbAnalogOut[en_AnalogIO_Number];
    
    double db12V_Voltag;
    double db12V_Current;
    double db24V_Voltag;
    double db24V_Current;
    double db48VIN_Voltag;
    double db48VIN_Current;
    double db48VOUT_Voltag;
    double db48VOUT_Current;

    _ST_EleBoxBuf():nVerYear(0),nVerDate(0),nEmergencyStop(0),nSafetyGuardStop(0),
        nResetSignal_EmergencyStop(0),nResetSignal_SafetyGuardStop(0),
        nRemoteSignal(0),nThreeStageSwitch_Signal(0.0),db12V_Voltag(0.0),
        db12V_Current(0),db24V_Voltag(0),db24V_Current(0),db48VIN_Voltag(0),
        db48VIN_Current(0),db48VOUT_Voltag(0),db48VOUT_Current(0.0)
    {
    	memset(nDI,0,sizeof(int)*en_IO_Number);
		memset(nDO,0,sizeof(int)*en_IO_Number);
		memset(nSI,0,sizeof(int)*en_IO_Number);
		memset(nSO,0,sizeof(int)*en_IO_Number);

		memset(nAnalogIN,0,sizeof(int)*en_AnalogIO_Number);
		memset(nAnalogOutMode,0,sizeof(int)*en_AnalogIO_Mode_Number);
		memset(dbAnalogOut,0,sizeof(int)*en_AnalogIO_Number);
    }

	/* 传参构造韩函数 */
	_ST_EleBoxBuf(const _ST_EleBoxBuf& obj)
    {
    	*this = obj;
    }

	/* 符号重载 */
	_ST_EleBoxBuf& operator=(const _ST_EleBoxBuf& obj)
	{
		Copy(this, obj);
		return *this;
	}
private:
	void Copy(_ST_EleBoxBuf* pThis, const _ST_EleBoxBuf& obj)
	{
		pThis->nVerYear = obj.nVerYear;
		pThis->nVerDate = obj.nVerDate;
		pThis->nEmergencyStop = obj.nEmergencyStop;
		pThis->nSafetyGuardStop = obj.nSafetyGuardStop;
		pThis->nResetSignal_EmergencyStop = obj.nResetSignal_EmergencyStop;
		pThis->nResetSignal_SafetyGuardStop = obj.nResetSignal_SafetyGuardStop;
		pThis->nRemoteSignal = obj.nRemoteSignal;
		pThis->nThreeStageSwitch_Signal = obj.nThreeStageSwitch_Signal;

		memcpy(pThis->nDI,obj.nDI,sizeof(int)*en_IO_Number);
		memcpy(pThis->nDO,obj.nDO,sizeof(int)*en_IO_Number);
		memcpy(pThis->nSI,obj.nSI,sizeof(int)*en_IO_Number);
		memcpy(pThis->nSO,obj.nSO,sizeof(int)*en_IO_Number);

		memcpy(pThis->nAnalogIN,obj.nAnalogIN,sizeof(int)*en_AnalogIO_Number);
		memcpy(pThis->nAnalogOutMode,obj.nAnalogOutMode,sizeof(int)*en_AnalogIO_Mode_Number);
		memcpy(pThis->dbAnalogOut,obj.dbAnalogOut,sizeof(int)*en_AnalogIO_Number);

		pThis->db12V_Voltag = obj.db12V_Voltag;
		pThis->db12V_Current = obj.db12V_Current;
		pThis->db24V_Voltag = obj.db24V_Voltag;
		pThis->db24V_Current = obj.db24V_Current;
		pThis->db48VIN_Voltag = obj.db48VIN_Voltag;
		pThis->db48VIN_Current = obj.db48VIN_Current;
		pThis->db48VOUT_Voltag = obj.db48VOUT_Voltag;
		pThis->db48VOUT_Current = obj.db48VOUT_Current;
	}

}ST_EleBoxBuf;


class SaftLock
{
public:
    SaftLock(){
        pthread_mutex_init(&m_lock,nullptr);
    }

    ~SaftLock(){
        pthread_mutex_destroy(&m_lock);
    }

    void Lock(){
        pthread_mutex_lock(&m_lock);
    }

    void unLock(){
        pthread_mutex_unlock(&m_lock);
    }

private:
    pthread_mutex_t m_lock;

};

class AutoSaftMutex
{
public:
    AutoSaftMutex(SaftLock *hLock):m_Lock(hLock)
    {
        m_Lock->Lock();
    }

    ~AutoSaftMutex()
    {
        m_Lock->unLock();
    }

private:
    SaftLock* m_Lock;    
};



#endif // !__PUBLICDEF_H_

