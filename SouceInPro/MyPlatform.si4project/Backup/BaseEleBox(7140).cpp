#include "BaseEleBox.h"

BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort)
{
	switch(EN_EleBox_Type)
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
			/* 返回4代电箱 */
			AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(nDeviceID,strIp,nPort);
			}
			
			return m_pEleBox;
			
			break;

		default:
			return nullptr;
	}
}


BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,string strPath)
{
	switch(EN_EleBox_Type)
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
			/* 返回4代电箱 */
			AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(strPath);
			}
			
			return m_pEleBox;
			
			break;

		default:
			return nullptr;
	}
}


