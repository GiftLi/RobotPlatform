#include "HRStatus.h"

struct stateMachine HRStatus::g_rbtfsm;
//初始化状态
struct state HRStatus::state_LoadConfig;
struct state HRStatus::state_Initialize;
struct state HRStatus::state_Reseting;

//电箱状态
struct state HRStatus::state_ElectricBoxDisconnect;

//急停状态
struct state HRStatus::state_EmergencyStopHandling;
struct state HRStatus::state_EmergencyStop;

//48V供电状态
//struct state HRStatus::state_Poweredby48V;
struct state HRStatus::state_Powering48V;
struct state HRStatus::state_Poweroff48V;

//安全光幕状态
struct state HRStatus::state_SafetyGuardHandling;
struct state HRStatus::state_SafetyGuard;

//控制器状态
struct state HRStatus::state_ControllerDisconnect;
struct state HRStatus::state_ControllerConnecting;
struct state HRStatus::state_EtherCATError;
struct state HRStatus::state_EtherCATResetting;

//机器人状态
struct state HRStatus::state_RobotOutofSafeSpace;
struct state HRStatus::state_RobotCollisionStop;
struct state HRStatus::state_RobotError;
struct state HRStatus::state_RobotDisable;
struct state HRStatus::state_RobotDisabling;
struct state HRStatus::state_RobotEnabling;
struct state HRStatus::state_RobotMoving;
struct state HRStatus::state_RobotStopping;
struct state HRStatus::state_RobotOpeningFreeDriver;
struct state HRStatus::state_RobotClosingFreeDriver;
struct state HRStatus::state_RobotFreeDriver;
struct state HRStatus::state_RobotStandy;


//外设状态


void HRStatus::InitializeStatus()
{
//初始化状态
   state_LoadConfig.parentState = NULL;
   state_LoadConfig.entryState = &state_Initialize;
   state_LoadConfig.transitions.push_back({Event_Msg, Cmd_RobotLoadCfg, NULL, &action_LoadCfg, &HRStatus::state_Initialize});
   state_LoadConfig.numTransitions = state_LoadConfig.transitions.size();
   state_LoadConfig.data = NULL;//"LoadConfig";
   state_LoadConfig.entryAction = NULL;//Handle_EntryLoadConfig;
   state_LoadConfig.exitAction = NULL;

   state_Initialize.parentState = NULL;
   state_Initialize.entryState = NULL;
   //state_Initialize.transitions = Initialize_transition;
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_Poweroff48V, &guard_Poweroff48V, NULL, &HRStatus::state_Poweroff48V});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_SafetyGuard, &guard_SafetyGuard, NULL, &HRStatus::state_SafetyGuardHandling});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_ControllerDisconnect, &guard_ControllerDisconnect, NULL, &HRStatus::state_ControllerDisconnect});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_EtherCATError, &guard_EtherCATError, NULL, &HRStatus::state_EtherCATError});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotOutofSafeSpace, &guard_RobotOutofSafeSpace, NULL, &HRStatus::state_RobotOutofSafeSpace});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotCollisionStop, &guard_RobotCollisionStop, NULL, &HRStatus::state_RobotCollisionStop});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotError, &guard_RobotError, NULL, &HRStatus::state_RobotError});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotDisable, &guard_RobotDisable, NULL, &HRStatus::state_RobotDisable});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotEnabling, &guard_RobotEnabling, NULL, &HRStatus::state_RobotEnabling});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotMoving, &guard_RobotMoving, NULL, &HRStatus::state_RobotMoving});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotStopping, &guard_RobotStopping, NULL, &HRStatus::state_RobotStopping});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotFreeDriver, &guard_RobotFreeDriver, NULL, &HRStatus::state_RobotFreeDriver});
   state_Initialize.transitions.push_back({Event_Timer, Cmd_CheckIs_RobotStandy, &guard_RobotStandy, NULL, &HRStatus::state_RobotStandy});
   state_Initialize.numTransitions = state_Initialize.transitions.size();
   state_Initialize.data = NULL;//"Initialize";
   state_Initialize.entryAction = Handle_EntryInitialize;
   state_Initialize.exitAction = NULL;

   state_Reseting.parentState = NULL;
   state_Reseting.entryState = NULL;
   state_Reseting.transitions = state_Initialize.transitions;
   state_Reseting.numTransitions = state_Reseting.transitions.size();
   state_Reseting.data = NULL;//"Initialize";
   state_Reseting.entryAction = Handle_EntryReseting;
   state_Reseting.exitAction = NULL;
//电箱状态
   state_ElectricBoxDisconnect.parentState = NULL;
   state_ElectricBoxDisconnect.entryState = NULL;
   state_ElectricBoxDisconnect.transitions.push_back({Event_Msg, Cmd_ConnectToBox, NULL, &action_ConnectToBox, &HRStatus::state_Initialize});
   state_ElectricBoxDisconnect.numTransitions = state_ElectricBoxDisconnect.transitions.size();
   state_ElectricBoxDisconnect.data = NULL;//"Initialize";
   state_ElectricBoxDisconnect.entryAction = Handle_EntryElectricBoxDisconnect;
   state_ElectricBoxDisconnect.exitAction = NULL;

//急停状态
   state_EmergencyStopHandling.parentState = NULL;
   state_EmergencyStopHandling.entryState = NULL;
   state_EmergencyStopHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_EmergencyStopHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStopHandling, &guard_EmergencyStopHandling, NULL, &HRStatus::state_EmergencyStop});
   state_EmergencyStopHandling.numTransitions = state_EmergencyStopHandling.transitions.size();
   state_EmergencyStopHandling.data = NULL;//"Initialize";
   state_EmergencyStopHandling.entryAction = Handle_EntryEmergencyStopHandling;
   state_EmergencyStopHandling.exitAction = NULL;

   state_EmergencyStop.parentState = NULL;
   state_EmergencyStop.entryState = NULL;
   state_EmergencyStop.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_EmergencyStop.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotResetEmergencyStop, &HRStatus::state_Reseting});
   state_EmergencyStop.numTransitions = state_EmergencyStop.transitions.size();
   state_EmergencyStop.data = NULL;//"Initialize";
   state_EmergencyStop.entryAction = Handle_EntryEmergencyStop;
   state_EmergencyStop.exitAction = NULL;

//安全光幕状态
   state_SafetyGuardHandling.parentState = NULL;
   state_SafetyGuardHandling.entryState = NULL;
   state_SafetyGuardHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_SafetyGuardHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_SafetyGuardHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_Poweroff48V, &guard_Poweroff48V, NULL, &HRStatus::state_Poweroff48V});
   state_SafetyGuardHandling.transitions.push_back({Event_Timer, Cmd_CheckIs_SafetyGuardHandling, &guard_SafetyGuardHandling, NULL, &HRStatus::state_SafetyGuard});
   state_SafetyGuardHandling.numTransitions = state_SafetyGuardHandling.transitions.size();
   state_SafetyGuardHandling.data = NULL;//"Initialize";
   state_SafetyGuardHandling.entryAction = Handle_EntrySafetyGuardHandling;
   state_SafetyGuardHandling.exitAction = NULL;

   state_SafetyGuard.parentState = NULL;
   state_SafetyGuard.entryState = NULL;
   state_SafetyGuard.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_SafetyGuard.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_SafetyGuard.transitions.push_back({Event_Timer, Cmd_CheckIs_Poweroff48V, &guard_Poweroff48V, NULL, &HRStatus::state_Poweroff48V});
   state_SafetyGuard.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotResetSafetyGuard, &HRStatus::state_Reseting});
   state_SafetyGuard.numTransitions = state_SafetyGuard.transitions.size();
   state_SafetyGuard.data = NULL;//"Initialize";
   state_SafetyGuard.entryAction = Handle_EntrySafetyGuard;
   state_SafetyGuard.exitAction = NULL;

//48V供电状态
   state_Poweroff48V.parentState = NULL;
   state_Poweroff48V.entryState = NULL;
   state_Poweroff48V.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_Poweroff48V.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_Poweroff48V.transitions.push_back({Event_Timer, Cmd_CheckIs_SafetyGuard, &guard_SafetyGuard, NULL, &HRStatus::state_SafetyGuardHandling});
   state_Poweroff48V.transitions.push_back({Event_Msg, Cmd_RobotElectrify, NULL, &action_RobotElectrify, &HRStatus::state_Powering48V});
   state_Poweroff48V.numTransitions = state_Poweroff48V.transitions.size();
   state_Poweroff48V.data = NULL;//"Initialize";
   state_Poweroff48V.entryAction = Handle_EntryPoweroff48V;
   state_Poweroff48V.exitAction = NULL;

   state_Powering48V.parentState = NULL;
   state_Powering48V.entryState = NULL;
   state_Powering48V.transitions = state_Initialize.transitions;
   state_Powering48V.numTransitions = state_Powering48V.transitions.size();
   state_Powering48V.data = NULL;//"Initialize";
   state_Powering48V.entryAction = Handle_EntryPowering48V;
   state_Powering48V.exitAction = NULL;

//控制器状态
   state_ControllerDisconnect.parentState = NULL;
   state_ControllerDisconnect.entryState = NULL;
   state_ControllerDisconnect.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_ControllerDisconnect.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_ControllerDisconnect.transitions.push_back({Event_Timer, Cmd_CheckIs_Poweroff48V, &guard_Poweroff48V, NULL, &HRStatus::state_Poweroff48V});
   state_ControllerDisconnect.transitions.push_back({Event_Timer, Cmd_CheckIs_SafetyGuard, &guard_SafetyGuard, NULL, &HRStatus::state_SafetyGuardHandling});
   state_ControllerDisconnect.transitions.push_back({Event_Msg, Cmd_ConnectToController, NULL, &action_ConnectToController, &HRStatus::state_ControllerConnecting});
   state_ControllerDisconnect.numTransitions = state_ControllerDisconnect.transitions.size();
   state_ControllerDisconnect.data = NULL;//"Initialize";
   state_ControllerDisconnect.entryAction = Handle_EntryControllerDisconnect;
   state_ControllerDisconnect.exitAction = NULL;

   state_ControllerConnecting.parentState = NULL;
   state_ControllerConnecting.entryState = NULL;
   state_ControllerConnecting.transitions = state_Initialize.transitions;
   state_ControllerConnecting.numTransitions = state_ControllerConnecting.transitions.size();
   state_ControllerConnecting.data = NULL;//"Initialize";
   state_ControllerConnecting.entryAction = Handle_EntryControllerConnecting;
   state_ControllerConnecting.exitAction = NULL;

   state_EtherCATError.parentState = NULL;
   state_EtherCATError.entryState = NULL;
   state_EtherCATError.transitions.push_back({Event_Timer, Cmd_CheckIs_BoxDisconnect, &guard_BoxDisconnect, NULL, &HRStatus::state_ElectricBoxDisconnect});
   state_EtherCATError.transitions.push_back({Event_Timer, Cmd_CheckIs_EmergencyStop, &guard_EmergencyStop, NULL, &HRStatus::state_EmergencyStopHandling});
   state_EtherCATError.transitions.push_back({Event_Timer, Cmd_CheckIs_Poweroff48V, &guard_Poweroff48V, NULL, &HRStatus::state_Poweroff48V});
   state_EtherCATError.transitions.push_back({Event_Timer, Cmd_CheckIs_SafetyGuard, &guard_SafetyGuard, NULL, &HRStatus::state_SafetyGuardHandling});
   state_EtherCATError.transitions.push_back({Event_Timer, Cmd_CheckIs_ControllerDisconnect, &guard_ControllerDisconnect, NULL, &HRStatus::state_ControllerDisconnect});
   state_EtherCATError.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotResetEtherCAT, &HRStatus::state_EtherCATResetting});
   state_EtherCATError.numTransitions = state_EtherCATError.transitions.size();
   state_EtherCATError.data = NULL;//"Initialize";
   state_EtherCATError.entryAction = Handle_EntryEtherCATError;
   state_EtherCATError.exitAction = NULL;

   state_EtherCATResetting.parentState = NULL;
   state_EtherCATResetting.entryState = NULL;
   state_EtherCATResetting.transitions = state_Initialize.transitions;
   state_EtherCATResetting.numTransitions = state_EtherCATResetting.transitions.size();
   state_EtherCATResetting.data = NULL;//"Initialize";
   state_EtherCATResetting.entryAction = Handle_EntryEtherCATResetting;
   state_EtherCATResetting.exitAction = NULL;

//机器人状态
   state_RobotOutofSafeSpace.parentState = NULL;
   state_RobotOutofSafeSpace.entryState = NULL;
   state_RobotOutofSafeSpace.transitions = state_Initialize.transitions;
   state_RobotOutofSafeSpace.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotReset, &HRStatus::state_Reseting});
   state_RobotOutofSafeSpace.transitions.push_back({Event_Msg, Cmd_SetOverride, NULL, &action_RobotSetOverride, &HRStatus::state_Reseting});
   state_RobotOutofSafeSpace.transitions.push_back({Event_Msg, Cmd_RobotMoveToSS, NULL, &action_RobotMoveToSS, &HRStatus::state_RobotMoving});
   state_RobotOutofSafeSpace.numTransitions = state_RobotOutofSafeSpace.transitions.size();
   state_RobotOutofSafeSpace.data = NULL;//"Initialize";
   state_RobotOutofSafeSpace.entryAction = Handle_EntryRobotOutofSafeSpace;
   state_RobotOutofSafeSpace.exitAction = NULL;

   state_RobotCollisionStop.parentState = NULL;
   state_RobotCollisionStop.entryState = NULL;
   state_RobotCollisionStop.transitions = state_Initialize.transitions;
   state_RobotCollisionStop.transitions.push_back({Event_Msg, Cmd_SetOverride, NULL, &action_RobotSetOverride, &HRStatus::state_Reseting});
   state_RobotCollisionStop.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotReset, &HRStatus::state_Reseting});
   state_RobotCollisionStop.numTransitions = state_RobotCollisionStop.transitions.size();
   state_RobotCollisionStop.data = NULL;//"Initialize";
   state_RobotCollisionStop.entryAction = Handle_EntryRobotCollisionStop;
   state_RobotCollisionStop.exitAction = NULL;

   state_RobotError.parentState = NULL;
   state_RobotError.entryState = NULL;
   state_RobotError.transitions = state_Initialize.transitions;
   state_RobotError.transitions.push_back({Event_Msg, Cmd_RobotReset, NULL, &action_RobotReset, &HRStatus::state_Reseting});
   state_RobotError.numTransitions = state_RobotError.transitions.size();
   state_RobotError.data = NULL;//"Initialize";
   state_RobotError.entryAction = Handle_EntryRobotError;
   state_RobotError.exitAction = NULL;

   state_RobotDisable.parentState = NULL;
   state_RobotDisable.entryState = NULL;
   state_RobotDisable.transitions = state_Initialize.transitions;
   state_RobotDisable.transitions.push_back({Event_Msg, Cmd_SetOverride, NULL, &action_RobotSetOverride, &HRStatus::state_Reseting});
   state_RobotDisable.transitions.push_back({Event_Msg, Cmd_RobotEnable, NULL, &action_RobotEnable, &HRStatus::state_RobotEnabling});
   state_RobotDisable.transitions.push_back({Event_Msg, Cmd_RobotPowerOn, NULL, &action_RobotEnable, &HRStatus::state_RobotEnabling});
   state_RobotDisable.numTransitions = state_RobotDisable.transitions.size();
   state_RobotDisable.data = NULL;//"Initialize";
   state_RobotDisable.entryAction = Handle_EntryRobotDisable;
   state_RobotDisable.exitAction = NULL;

   state_RobotDisabling.parentState = NULL;
   state_RobotDisabling.entryState = NULL;
   state_RobotDisabling.transitions = state_Initialize.transitions;
   state_RobotDisabling.numTransitions = state_RobotDisabling.transitions.size();
   state_RobotDisabling.data = NULL;//"Initialize";
   state_RobotDisabling.entryAction = Handle_EntryRobotDisabling;
   state_RobotDisabling.exitAction = NULL;

   state_RobotEnabling.parentState = NULL;
   state_RobotEnabling.entryState = NULL;
   state_RobotEnabling.transitions = state_Initialize.transitions;
   state_RobotEnabling.numTransitions = state_RobotEnabling.transitions.size();
   state_RobotEnabling.data = NULL;//"Initialize";
   state_RobotEnabling.entryAction = Handle_EntryRobotEnabling;
   state_RobotEnabling.exitAction = NULL;

   state_RobotMoving.parentState = NULL;
   state_RobotMoving.entryState = NULL;
   state_RobotMoving.transitions = state_Initialize.transitions;
   state_RobotMoving.transitions.push_back({Event_Msg, Cmd_RobotStop, NULL, &action_RobotStop, &HRStatus::state_RobotStopping});
   state_RobotMoving.numTransitions = state_RobotMoving.transitions.size();
   state_RobotMoving.data = NULL;//"Initialize";
   state_RobotMoving.entryAction = Handle_EntryRobotMoving;
   state_RobotMoving.exitAction = NULL;

   state_RobotStopping.parentState = NULL;
   state_RobotStopping.entryState = NULL;
   state_RobotStopping.transitions = state_Initialize.transitions;
   state_RobotStopping.numTransitions = state_RobotStopping.transitions.size();
   state_RobotStopping.data = NULL;//"Initialize";
   state_RobotStopping.entryAction = Handle_EntryRobotStopping;
   state_RobotStopping.exitAction = NULL;

   state_RobotOpeningFreeDriver.parentState = NULL;
   state_RobotOpeningFreeDriver.entryState = NULL;
   state_RobotOpeningFreeDriver.transitions = state_Initialize.transitions;
   state_RobotOpeningFreeDriver.numTransitions = state_RobotOpeningFreeDriver.transitions.size();
   state_RobotOpeningFreeDriver.data = NULL;//"Initialize";
   state_RobotOpeningFreeDriver.entryAction = Handle_EntryRobotOpeningFreeDriver;
   state_RobotOpeningFreeDriver.exitAction = NULL;

   state_RobotClosingFreeDriver.parentState = NULL;
   state_RobotClosingFreeDriver.entryState = NULL;
   state_RobotClosingFreeDriver.transitions = state_Initialize.transitions;
   state_RobotClosingFreeDriver.numTransitions = state_RobotClosingFreeDriver.transitions.size();
   state_RobotClosingFreeDriver.data = NULL;//"Initialize";
   state_RobotClosingFreeDriver.entryAction = Handle_EntryRobotClosingFreeDriver;
   state_RobotClosingFreeDriver.exitAction = NULL;
   
   state_RobotFreeDriver.parentState = NULL;
   state_RobotFreeDriver.entryState = NULL;
   state_RobotFreeDriver.transitions = state_Initialize.transitions;
   state_RobotFreeDriver.transitions.push_back({Event_Msg, Cmd_RobotCloseFreeDriver, NULL, &action_RobotCloseFreeDriver, &HRStatus::state_RobotClosingFreeDriver});
   state_RobotFreeDriver.numTransitions = state_RobotFreeDriver.transitions.size();
   state_RobotFreeDriver.data = NULL;//"Initialize";
   state_RobotFreeDriver.entryAction = Handle_EntryRobotFreeDriver;
   state_RobotFreeDriver.exitAction = NULL;

   state_RobotStandy.parentState = NULL;
   state_RobotStandy.entryState = NULL;
   state_RobotStandy.transitions = state_Initialize.transitions;
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_SetOverride, NULL, &action_RobotSetOverride, &HRStatus::state_Reseting});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotStop, NULL, &action_RobotStop, &HRStatus::state_RobotStopping});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotDisable, NULL, &action_RobotDisable, &HRStatus::state_RobotDisabling});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotPowerOff, NULL, &action_RobotDisable, &HRStatus::state_RobotDisabling});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotMoveJ, NULL, &action_RobotMoveJ, &HRStatus::state_RobotMoving});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotMoveL, NULL, &action_RobotMoveL, &HRStatus::state_RobotMoving});
   state_RobotStandy.transitions.push_back({Event_Msg, Cmd_RobotOpenFreeDriver, NULL, &action_RobotOpenFreeDriver, &HRStatus::state_RobotOpeningFreeDriver});
   state_RobotStandy.numTransitions = state_RobotStandy.transitions.size();
   state_RobotStandy.data = NULL;//"Standy";
   state_RobotStandy.entryAction = Handle_EntryRobotStandy;
   state_RobotStandy.exitAction = NULL;

//外设状态
}


