#ifndef __PUBLICDEF_H_
#define __PUBLICDEF_H_
#include <pthread.h>


typedef enum _EN_EleBox_Type
{
	en_EleBox_Type_V1=1,
	en_EleBox_Type_V2,
	en_EleBox_Type_V3,
	en_EleBox_Type_V4,
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

