#include "EleBoxFactory.h"

EleBoxFactory* EleBoxFactory::pEleBoxFactoryInstance = nullptr;
SaftLock EleBoxFactory::m_EleBox_factory_lock;

EleBoxFactory* EleBoxFactory::getEleBoxFactoryInstance()
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
	if(nullptr == pEleBoxFactoryInstance)
	{
		pEleBoxFactoryInstance = new EleBoxFactory();
	}
	
	return pEleBoxFactoryInstance;
	
}


BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort)
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);

	switch(enVersion)
	{
		case en_EleBox_Type_V1:
			/* 返回1代电箱 */
		
			break;

		case en_EleBox_Type_V2:
			/* 返回2代电箱 */
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV2(nDeviceID,strIp,nPort);
			}
			
			break;

		case en_EleBox_Type_V3:
			/* 返回3代电箱 */
		
			break;

		case en_EleBox_Type_V4:
			/* 返回4代电箱 */
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(nDeviceID,strIp,nPort);
			}
			
			break;

		case en_EleBox_Type_Simulation:
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxSimulation(nDeviceID,strIp,nPort);
			}

			break;
			
		default:
			return nullptr;
	}

		return m_pEleBox;
}


BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,string strPath)
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);

	switch(enVersion)
	{
		case en_EleBox_Type_V1:
			/* 返回1代电箱 */
		
			break;

		case en_EleBox_Type_V2:
			/* 返回2代电箱 */
		
			break;

		case en_EleBox_Type_V3:
			/* 返回3代电箱 */
		
			break;

		case en_EleBox_Type_V4:
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(strPath);
			}

			break;

		case en_EleBox_Type_Simulation:
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxSimulation(strPath);
			}

			break;

		default:
			return nullptr;
	}

	return m_pEleBox;
}

BaseEleBox* EleBoxFactory::getEleBoxInstance()
{
	
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
	if(nullptr == m_pEleBox)
	{
		printf("please init Box by [INIT_ELEBOX_TCP_INSTANCE] or [INIT_ELEBOX_RTU_INSTANCE]\n");

		return nullptr;
	}
	
	return m_pEleBox;
}



