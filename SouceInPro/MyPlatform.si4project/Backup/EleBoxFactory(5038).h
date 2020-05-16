#pragma once
#include <string>
#include "BaseEleBox.h"
#include "EleBoxV4.h"
#include "EleBoxV2.h"
#include "EleBoxSimulation.h"

#define INIT_ELEBOX_TCP_INSTANCE(EleBox_Type,nDeviceID,strIp,nPort) \
			(EleBoxFactory::getEleBoxFactoryInstance()->getEleBoxInstance(EleBox_Type,nDeviceID,strIp,nPort))

#define INIT_ELEBOX_RTU_INSTANCE(EleBox_Type,strSerialPath)  \
			(EleBoxFactory::getEleBoxFactoryInstance()->getEleBoxInstance(EleBox_Type,strSerialPath))

#define GET_ELEBOX_INSTANCE() \
			(EleBoxFactory::getEleBoxFactoryInstance()->getEleBoxInstance())



#define FILE_PATH "/usr/local/etc/Motion/Box.ini"

string GetIniKeyString(string title,string key);
int GetIniKeyInt(string title,string key);

class EleBoxBaseFactory
{
public:
	EleBoxBaseFactory();
	virtual ~EleBoxBaseFactory();

	virtual BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)=0;
	virtual BaseEleBox* createEleBoxInstance(const string strPath)=0;
};



class EleBoxV2Factory:public EleBoxBaseFactory
{
public:
	EleBoxFactory(){}
	virtual ~EleBoxFactory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);
#if 0

	static EleBoxFactory* getEleBoxFactoryInstance();
	
    BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort);
    BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,string strPath);
	BaseEleBox* getEleBoxInstance();

private:
    static EleBoxFactory* pEleBoxFactoryInstance;
	
   	BaseEleBox* m_pEleBox;

   static SaftLock m_EleBox_factory_lock;
#endif
};

class EleBoxV4Factory:public EleBoxBaseFactory
{
public:
	EleBoxFactory(){}
	virtual ~EleBoxFactory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);
};


class EleBoxSimulationFactory:public EleBoxBaseFactory
{
public:
	EleBoxFactory(){}
	virtual ~EleBoxFactory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);
};

