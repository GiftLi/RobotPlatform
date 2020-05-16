#include "MainForm.h"

SaftLock RobotControlMainForm::m_lMainFormLock;
BaseEleBox* RobotControlMainForm::m_pEleBoxInstance = nullptr;
RobotControlMainForm* RobotControlMainForm::m_pMainForm = new RobotControlMainForm();


RobotControlMainForm::RobotControlMainForm()
{
	m_pEleBoxFactory = nullptr;
	
	/* 根据配置文件确定创建电箱 */
	bool bFlg = createEleBoxFactory(EN_EleBox_Type(GetIniKeyInt("SystemBoard","Type")));
	
	if(!bFlg)
	{
		printf("Create EleBox Instance Error! Please checking Bon.ini file\n");

		return;
	}

}

RobotControlMainForm* RobotControlMainForm::getMainFormInstance(void)
{
	AutoSaftMutex MainFormLock(&m_lMainFormLock);

	if(nullptr == m_pMainForm)
	{
		m_pMainForm = new RobotControlMainForm();
	}
	
	return m_pMainForm;
}


bool RobotControlMainForm::createEleBoxFactory(EN_EleBox_Type enEleBoxType)
{
	switch (enEleBoxType)
	{
		case en_EleBox_Type_Simulation:
			
			m_pEleBoxFactory = new EleBoxSimulationFactory();

			break;

		case en_EleBox_Type_V1:
			//m_pEleBoxFactory = new EleBoxV1Factory();
			
			break;

		case en_EleBox_Type_V2:

			m_pEleBoxFactory = new EleBoxV2Factory();

			break;

		case en_EleBox_Type_V3:
			//m_pEleBoxFactory = new EleBoxV3Factory();
			
			break;

		case en_EleBox_Type_V4:

			m_pEleBoxFactory = new EleBoxV4Factory();
			
			break;

		default:
			return false;
	}

	return nullptr != m_pEleBoxFactory;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

BaseEleBox* RobotControlMainForm::createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)
{
	AutoSaftMutex EleBoxSingleObjLock(&m_lEleBoxSingleObjLock);

	if(nullptr == m_pEleBoxInstance)
	{
		m_pEleBoxInstance = m_pEleBoxFactory->createEleBoxInstance(nDeviceID,strIp,nPort);
	}
	
	return m_pEleBoxInstance;
}

BaseEleBox* RobotControlMainForm::createEleBoxInstance(const string strPath)
{
	AutoSaftMutex EleBoxSingleObjLock(&m_lEleBoxSingleObjLock);

	if(nullptr == m_pEleBoxInstance)
	{
		m_pEleBoxInstance = m_pEleBoxFactory->createEleBoxInstance(strPath);
	}
	
	return m_pEleBoxInstance;
	
}


BaseEleBox* RobotControlMainForm::getEleBoxInstance(void)
{
	AutoSaftMutex EleBoxSingleObjLock(&m_lEleBoxSingleObjLock);

	if(nullptr == m_pEleBoxInstance)
	{
		printf("getEleBoxInstance Error !!! Please Create EleBox Instance before getting Obj\n");
	}
	
	return m_pEleBoxInstance;
}





