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


class EleBoxFactory
{
public:
	EleBoxFactory(){}
	~EleBoxFactory(){}

	static EleBoxFactory* getEleBoxFactoryInstance();
	
    BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort);
    BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,string strPath);
	BaseEleBox* getEleBoxInstance();

private:
    static EleBoxFactory* pEleBoxFactoryInstance;
	
   	BaseEleBox* m_pEleBox;

   static SaftLock m_EleBox_factory_lock;
};

