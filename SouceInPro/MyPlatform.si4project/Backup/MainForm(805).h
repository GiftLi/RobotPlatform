#pragma once

#include "../Platform_EleBox/ElectricityBox/EleBoxFactory.h"

class RobotControlMainForm
{
public:
	RobotControlMainForm()
	{
		pEleBoxFactory = nullptr;
		
		/* 根据配置文件确定创建电箱 */
		bool bFlg = createEleBoxInstance(EN_EleBox_Type(GetIniKeyInt("SystemBoard","Type")));
		if(!bFlg)
		{
			printf("Create EleBox Instance Error! Please checking Bon.ini file\n");

			return;
		}
	}
	
	~RobotControlMainForm();

public:	
	EleBoxBaseFactory* m_pEleBoxFactory; 

public:
	bool createEleBoxInstance(EN_EleBox_Type enEleBoxType)
	{
		switch (enEleBoxType)
		{
			case en_EleBox_Type_Simulation:
				
				m_pEleBoxFactory = EleBoxSimulationFactory();

				break;

			case en_EleBox_Type_V1:
				//m_pEleBoxFactory = EleBoxV1Factory();
				
				break;

			case en_EleBox_Type_V2:

				m_pEleBoxFactory = EleBoxV2Factory();

				break;

			case en_EleBox_Type_V3:
				//m_pEleBoxFactory = EleBoxV3Factory();
				
				break;

			case en_EleBox_Type_V4:

				m_pEleBoxFactory = EleBoxV4Factory();
				
				break;

			default:
				return false;
		}

		return nullptr != m_pEleBoxFactory
	}
};

