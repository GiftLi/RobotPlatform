#pragma once

#include "../Platform_EleBox/ElectricityBox/EleBoxFactory.h"

#define INIT_ELEBOX_TCP_INSTANCE(nDeviceID,strIp,nPort) \
			(RobotControlMainForm::getMainFormInstance()->createEleBoxInstance(nDeviceID,strIp,nPort))

#define INIT_ELEBOX_RTU_INSTANCE(strSerialPath)  \
			(RobotControlMainForm::getMainFormInstance()->createEleBoxInstance(strSerialPath))

#define GET_ELEBOX_INSTANCE() \
			(RobotControlMainForm::getMainFormInstance()->getEleBoxInstance())

class RobotControlMainForm
{
public:
	RobotControlMainForm();
	~RobotControlMainForm(){};

public:
	static RobotControlMainForm* getMainFormInstance(void);

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);

	BaseEleBox* getEleBoxInstance(void);

private:
	bool createEleBoxFactory(EN_EleBox_Type enEleBoxType);

private:
	/* 主框架：单例 */
	static RobotControlMainForm* m_pMainForm;
	static SaftLock m_lMainFormLock;
	
	EleBoxBaseFactory* m_pEleBoxFactory; 

	/* 静态：电箱单例 */
	static BaseEleBox* m_pEleBoxInstance;
	/* 电箱单例锁：防止创建多个电箱实例 */
	SaftLock m_lEleBoxSingleObjLock;

	
	

};

