#ifndef _HR_STATUS_ROBOTFUNC_H
#define _HR_STATUS_ROBOTFUNC_H

#include "stateMachine.h"

#ifdef __cplusplus
extern "C"
{
#endif
bool action_LoadCfg(void *oldStateData, struct event *event, void *newStateData);
bool action_ConnectToBox(void *oldStateData, struct event *event, void *newStateData);
//void action_EmergencyStopHandling(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotResetEmergencyStop(void *oldStateData, struct event *event, void *newStateData);
bool action_ConnectToController(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotResetEtherCAT(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotResetSafetyGuard(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotElectrify(void *oldStateData, struct event *event, void *newStateData);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool action_RobotEnable(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotDisable(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotReset(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotStop(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotOpenFreeDriver(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotCloseFreeDriver(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotSetOverride(void *oldStateData, struct event *event, void *newStateData);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool action_RobotMoveToSS(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotMoveJ(void *oldStateData, struct event *event, void *newStateData);
bool action_RobotMoveL(void *oldStateData, struct event *event, void *newStateData);

#ifdef __cplusplus
}
#endif

#endif