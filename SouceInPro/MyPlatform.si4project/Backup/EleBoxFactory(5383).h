#pragma once
#include <string>
// #include "../../Platform_Public/publicDef.h"
#include "EleBoxV4.h"
#include "EleBoxSimulation.h"

#define INIT_ELEBOX_TCP_INSTANCE(EleBox_Type,nDeviceID,strIp,nPort) (EleBoxFactory::getEleBoxInstance(EleBox_Type,nDeviceID,strIp,nPort))

#define INIT_ELEBOX_RTU_INSTANCE(EleBox_Type,strSerialPath) (EleBoxFactory::getEleBoxInstance(EleBox_Type,strSerialPath))

#define GET_ELEBOX_INSTANCE() (EleBoxFactory::getEleBoxInstance())


class EleBoxFactory
{
public:
    static BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort);
    static BaseEleBox* getEleBoxInstance(EN_EleBox_Type enVersion,string strPath);
	static BaseEleBox* getEleBoxInstance();

private:
   static BaseEleBox* m_pEleBox;

   static SaftLock m_EleBox_factory_lock;
};

