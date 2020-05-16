
#include "hrc_if_xmlrpcServer.h"
#include <pthread.h>
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include <sys/prctl.h>
#include "HRC_Public/hrc_public_define/hrc_public_if_cmd.h"


/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace xmlrpcServer
{

    xmlrpc_server_abyss_parms HRDCS_xmlrpcServer::m_serverparm = { 0 };
    xmlrpc_env HRDCS_xmlrpcServer::m_env = { 0 };
    xmlrpc_registry * HRDCS_xmlrpcServer::m_registryP=nullptr;


    HRDCS_xmlrpcServer* HRDCS_xmlrpcServer::m_instance = nullptr;
    HRDCS_xmlrpcServer* HRDCS_xmlrpcServer::Instance()
    {
    	if (HRDCS_xmlrpcServer::m_instance == nullptr)
    	{
    		HRDCS_xmlrpcServer::m_instance = new HRDCS_xmlrpcServer;
    	}
    	return HRDCS_xmlrpcServer::m_instance;
    }

    int HRDCS_xmlrpcServer::StartServer(const char *log_file_name, int nPort)
    {
        m_serverparm.config_file_name = nullptr;   /* Select the modern normal API */
    	m_serverparm.registryP = m_registryP;
        m_serverparm.port_number = static_cast<unsigned int>(nPort);
    	m_serverparm.log_file_name = nullptr;

        pthread_t serverThread;
        if(pthread_create(&serverThread, nullptr, HRDCS_xmlrpcServer_work, nullptr) != 0)
        {
            center_trace(center_log_error,"pthread_create m_serverThread fail!!");
            return -1;
        }

    	return 0;

    }
    void* HRDCS_xmlrpcServer::HRDCS_xmlrpcServer_work(void* pVoid)
    {
    	prctl(PR_SET_NAME, (unsigned long)"xmlrpcServer");

    	xmlrpc_server_abyss(&m_env, &m_serverparm, XMLRPC_APSIZE(log_file_name));
    	if (m_env.fault_occurred)
    	{
            //printf("xmlrpc_server_abyss() failed.  %s\n", m_env.fault_string);
    	}
    	return nullptr;
    }
    HRDCS_xmlrpcServer::HRDCS_xmlrpcServer()
    {
    
    }


    HRDCS_xmlrpcServer::~HRDCS_xmlrpcServer()
    {
    }
    int HRDCS_xmlrpcServer::InitServer(int nPort)
    {
    	xmlrpc_env_init(&m_env);
    	m_registryP = xmlrpc_registry_new(&m_env);
    	RegsiterFunction();
        StartServer("xmlrpcServerLog.log", nPort);
    	return 0;
    }
    int HRDCS_xmlrpcServer::DeInitServer()
    {
    	return 0;
    }

    void HRDCS_xmlrpcServer::RegsiterFunction(const char *methodName, xmlrpc_method2 methodFunction)
    {
    	struct xmlrpc_method_info3 const methodInfo = {
    		/* .methodName     = */ methodName,
    		/* .methodFunction = */ methodFunction,
    	};
    	xmlrpc_registry_add_method3(&m_env, m_registryP, &methodInfo);
    }
    void HRDCS_xmlrpcServer::RegsiterFunction()
    {

        /*setRobot*/
        RegsiterFunction(Protocol_Electrify, xmlrpc_Electrify);
        RegsiterFunction(Protocol_Blackout, xmlrpc_Blackout);
        RegsiterFunction(Protocol_StartMaster, xmlrpc_StartMaster);
        RegsiterFunction(Protocol_CloseMaster, xmlrpc_CloseMaster);
        RegsiterFunction(Protocol_GrpResetEStop, xmlrpc_ResetEStop);
        RegsiterFunction(Protocol_GrpResetSGuard, xmlrpc_ResetSGuard);
    	RegsiterFunction(Protocol_GrpPowerOff, xmlrpc_GrpPowerOff);
    	RegsiterFunction(Protocol_GrpPowerOn, xmlrpc_GrpPowerOn);
    	RegsiterFunction(Protocol_GrpReset, xmlrpc_GrpReset);
    	RegsiterFunction(Protocol_GrpStop, xmlrpc_GrpStop);
        RegsiterFunction(Protocol_GrpInterrupt, xmlrpc_GrpInterrupt);
        RegsiterFunction(Protocol_GrpContinue, xmlrpc_GrpContinue);
    	RegsiterFunction(Protocol_SetStartAssistiveMode, xmlrpc_SetStartAssistiveMode);
    	RegsiterFunction(Protocol_SetCloseAssistiveMode, xmlrpc_SetCloseAssistiveMode);
        RegsiterFunction(Protocol_SetOverride, xmlrpc_SetOverride); 
        RegsiterFunction(Protocol_SetToolCoordinateMotion, xmlrpc_SetToolCoordinateMotion);


        /*moving*/
    	RegsiterFunction(Protocol_ShortJogJ, xmlrpc_ShortJogJ);
    	RegsiterFunction(Protocol_ShortJogL, xmlrpc_ShortJogL);
    	RegsiterFunction(Protocol_LongJogJ, xmlrpc_LongJogJ);
    	RegsiterFunction(Protocol_LongJogL, xmlrpc_LongJogL);
    	RegsiterFunction(Protocol_MoveRelJ, xmlrpc_MoveRelJ);
    	RegsiterFunction(Protocol_MoveRelL, xmlrpc_MoveRelL);
    	RegsiterFunction(Protocol_MoveJ, xmlrpc_MoveJ);
    	RegsiterFunction(Protocol_MoveL, xmlrpc_MoveL);
        RegsiterFunction(Protocol_MoveJTo, xmlrpc_MoveToACS);
        RegsiterFunction(Protocol_MoveLTo, xmlrpc_MoveToPCS);
    	RegsiterFunction(Protocol_StartPushBlending, xmlrpc_StartPushBlending);
    	RegsiterFunction(Protocol_PushBlendingPoint, xmlrpc_PushBlendingPoint);
        RegsiterFunction(Protocol_StartBlendingMotion, xmlrpc_StartBlendingMotion);
        RegsiterFunction(Protocol_MoveToSS, xmlrpc_MoveToSS);
        RegsiterFunction(Protocol_LongMoveEvent, xmlrpc_LongMoveEvent);
        

        /*setio*/
        RegsiterFunction(Protocol_SetBoxDO, xmlrpc_SetBoxDO);
        RegsiterFunction(Protocol_SetBoxCO, xmlrpc_SetBoxCO);
        RegsiterFunction(Protocol_SetBoxAO, xmlrpc_SetBoxAO);
        RegsiterFunction(Protocol_SetBoxAOMode, xmlrpc_SetBoxAOMode);
        RegsiterFunction(Protocol_SetEndDO, xmlrpc_SetEndDO);
        RegsiterFunction(Protocol_SetShutdownTime,xmlrpc_SetShutdownTime);

        /*setconfig*/
    	RegsiterFunction(Protocol_SetEmergencyForResetIO, xmlrpc_SetEmergencyForResetIO);
        RegsiterFunction(Protocol_SetSafetyGuardMonitor, xmlrpc_SetSafetyGuardMonitor);

    	RegsiterFunction(Protocol_SetKinematicCoordinate, xmlrpc_SetKinematicCoordinate);
        RegsiterFunction(Protocol_SetUserCoordinate, xmlrpc_SetUserCoordinate);
    	RegsiterFunction(Protocol_SetBaseMountingAngle, xmlrpc_SetBaseMountingAngle);
    	RegsiterFunction(Protocol_SetPayload, xmlrpc_SetPayload);
        //RegsiterFunction(Protocol_SetHomePosition, xmlrpc_SetHomePosition);
    	RegsiterFunction(Protocol_SetPcsSafeSpaceLimit, xmlrpc_SetPcsSafeSpaceLimit);
    	RegsiterFunction(Protocol_SetAcsSafeSpaceLimit, xmlrpc_SetAcsSafeSpaceLimit); 
    	RegsiterFunction(Protocol_SetMoveJointMotionLimits, xmlrpc_SetMoveJointMotionLimits);
    	RegsiterFunction(Protocol_SetMovePcsMotionLimits, xmlrpc_SetMovePcsMotionLimits);
    	RegsiterFunction(Protocol_SetStopJointMotionLimits, xmlrpc_SetStopJointMotionLimits); 
    	RegsiterFunction(Protocol_SetStopPcsMotionLimits, xmlrpc_SetStopPcsMotionLimits);
    	RegsiterFunction(Protocol_SetCollideLevel, xmlrpc_SetCollideLevel);
    	RegsiterFunction(Protocol_SetSafetyPanel, xmlrpc_SetSafetyPanel);

        RegsiterFunction(Protocol_SetEndDIConfig, xmlrpc_SetEndDIConfig);
        RegsiterFunction(Protocol_SetEndDOConfig, xmlrpc_SetEndDOConfig);
        RegsiterFunction(Protocol_SetEndAIConfig, xmlrpc_SetEndAIConfig);
        RegsiterFunction(Protocol_SetBoxAIConfig, xmlrpc_SetBoxAIConfig);
        RegsiterFunction(Protocol_SetBoxAOConfig, xmlrpc_SetBoxAOConfig);
        RegsiterFunction(Protocol_SetBoxCIConfig, xmlrpc_SetBoxCIConfig);
        RegsiterFunction(Protocol_SetBoxCOConfig, xmlrpc_SetBoxCOConfig);
        RegsiterFunction(Protocol_SetBoxDOConfig, xmlrpc_SetBoxDOConfig);
        RegsiterFunction(Protocol_SetBoxDIConfig, xmlrpc_SetBoxDIConfig);

        RegsiterFunction(Protocol_SetRobotScript, xmlrpc_SetRobotConfig); 
        RegsiterFunction(Protocol_SetRobotsHardConfig, xmlrpc_SetRobotHardConfig);
        RegsiterFunction(Protocol_SaveRobotHardConfig, xmlrpc_SaveRobotHardFile); 
        RegsiterFunction(Protocol_SaveRobotScript, xmlrpc_SaveScriptFile); 


        /*readrobot*/
    	RegsiterFunction(Protocol_TCP3PointCalculate, xmlrpc_TCP3PointCalculate);
    	RegsiterFunction(Protocol_TCPPositionCalculate, xmlrpc_TCPPositionCalculate);
    	RegsiterFunction(Protocol_TCPOrientationCalculate, xmlrpc_TCPOrientationCalculate);
    	RegsiterFunction(Protocol_IsSimulation, xmlrpc_IsSimulation);
    	RegsiterFunction(Protocol_UserPointCoordinateCalculate, xmlrpc_UserPointCoordinateCalculate);
    	RegsiterFunction(Protocol_UserLineCoordinateCalculate, xmlrpc_UserLineCoordinateCalculate);
    	RegsiterFunction(Protocol_UserPlaneCoordinateCalculate, xmlrpc_UserPlaneCoordinateCalculate);
    	RegsiterFunction(Protocol_ReadRobotID, xmlrpc_ReadRobotID);
        RegsiterFunction(Protocol_ReadRealTimeInfo, xmlrpc_ReadRealTimeInfo);
        RegsiterFunction(Protocol_PCS2ACS, xmlrpc_PCS2ACS);
        RegsiterFunction(Protocol_Base2UcsTcp, xmlrpc_Base2UcsTcp);
        RegsiterFunction(Protocol_UcsTcp2Base, xmlrpc_UcsTcp2Base);


        /*readconfig*/
    	RegsiterFunction(Protocol_ReadRobotsConfig, xmlrpc_ReadRobotsConfig);
    	RegsiterFunction(Protocol_ReadRobotsHardConfig, xmlrpc_ReadRobotsHardConfig);
        RegsiterFunction(Protocol_ReadSafeLevelConfig, xmlrpc_ReadSafeLevel);

        /*script*/
     	RegsiterFunction(Protocol_StartScript, xmlrpc_StartScript);
    	RegsiterFunction(Protocol_StopScript,  xmlrpc_StopScript);	
    	RegsiterFunction(Protocol_PauseScript, xmlrpc_PauseScript);
        RegsiterFunction(Protocol_ContinueScript, xmlrpc_ContinueScript);
        RegsiterFunction(Protocol_NextStepScript, xmlrpc_NextStepScript); 
        RegsiterFunction(Protocol_NextBreakPoint, xmlrpc_NextBreakPoint); 

        /*modbus*/
        RegsiterFunction(Protocol_AddModbusClientDevice, xmlrpc_AddModbusClientDevice);
        RegsiterFunction(Protocol_DelModbusClientDevice, xmlrpc_DelModbusClientDevice);
        RegsiterFunction(Protocol_SetModbusClientPamar, xmlrpc_SetModbusClientPamar);

        RegsiterFunction(Protocol_WriteModbusData, xmlrpc_WriteModbusData);
        RegsiterFunction(Protocol_ReadModbusData, xmlrpc_ReadModbusData);

        RegsiterFunction(Protocol_GetModbusClientIsConnection, xmlrpc_GetModbusClientIsConnection);


    	/*****************************************************************************/

    	//RegsiterFunction(Protocol_SetEmergencyForResetIOState, xmlrpc_SetEmergencyForResetIOState);
    	//RegsiterFunction(Protocol_SetSafetyGuardHold, xmlrpc_SetSafetyGuardHold);
        //RegsiterFunction(Protocol_SetNetworkIP, xmlrpc_SetNetworkIP);
    	/*RegsiterFunction(Protocol_ReadSafetyPanel, xmlrpc_ReadSafetyPanel);
    	RegsiterFunction(Protocol_ReadElectricityBoxDI, xmlrpc_ReadElectricityBoxDI);
    	RegsiterFunction(Protocol_ReadElectricityBoxSI, xmlrpc_ReadElectricityBoxSI);
    	RegsiterFunction(Protocol_ReadElectricityBoxExterDI, xmlrpc_ReadElectricityBoxExternDI);
    	RegsiterFunction(Protocol_ReadElectricityBoxDO, xmlrpc_ReadElectricityBoxDO);
    	RegsiterFunction(Protocol_ReadElectricityBoxSO, xmlrpc_ReadElectricityBoxSO);
    	RegsiterFunction(Protocol_ReadElectricityBoxExterDO, xmlrpc_ReadElectricityBoxExternDO);
    	RegsiterFunction(Protocol_ReadElectricityBoxAnalog, xmlrpc_ReadElectricityBoxAnalog);
    	RegsiterFunction(Protocol_ReadElectricityBoxPower, xmlrpc_ReadElectricityBoxPower);
    	RegsiterFunction(Protocol_ReadRTRbtEndIO, xmlrpc_ReadRTRbtEndIO);
    	RegsiterFunction(Protocol_ReadConveyorValue, xmlrpc_ReadConveyorValue);
        RegsiterFunction(Protocol_ReadEmergencyMonitor, xmlrpc_ReadEmergencyMonitor);
    	RegsiterFunction(Protocol_ReadEmergencyForResetIO, xmlrpc_ReadEmergencyForResetIO);
        RegsiterFunction(Protocol_ReadEmergencyForResetIOState, xmlrpc_ReadEmergencyForResetIOState);
        RegsiterFunction(Protocol_ReadSafetyGuardMonitor, xmlrpc_ReadSafetyGuardMonitor);
    	RegsiterFunction(Protocol_ReadSwitchOnMonitor, xmlrpc_ReadSwitchOnMonitor);
    	RegsiterFunction(Protocol_ReadConveyorConfig, xmlrpc_ReadConveyorConfig);
    	RegsiterFunction(Protocol_ReadInpositionConfig, xmlrpc_ReadInpositionConfig);
    	RegsiterFunction(Protocol_ReadNetworkIP, xmlrpc_ReadNetworkIP);
    	RegsiterFunction(Protocol_ReadSafetyGuardHold, xmlrpc_ReadSafetyGuardHold);*/
        //RegsiterFunction(Protocol_ReadRTRbtPCSForBase, xmlrpc_ReadRTRbtPCSForBase);
        //RegsiterFunction(Protocol_ReadRTRbtTOOL, xmlrpc_ReadRTRbtTOOL);
        //RegsiterFunction("kkkdfdf", xmlrpc_SetCollideLevelJSon);
        //RegsiterFunction(Protocol_SetOutIOState, xmlrpc_SetOutIOState);

    }

}
