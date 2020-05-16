#ifndef _HR_STATUS_FUNC_H
#define _HR_STATUS_FUNC_H

#include "stateMachine.h"

#ifdef __cplusplus
extern "C"
{
#endif

//void Handle_EntryLoadConfig( void *oldStateData, struct event *event);
void Handle_EntryInitialize( void *oldStateData, struct event *event);
void Handle_EntryReseting(void *oldStateData, struct event *event);
void Handle_EntryElectricBoxDisconnect( void *oldStateData, struct event *event);

void Handle_EntryEmergencyStopHandling( void *oldStateData, struct event *event);
void Handle_EntryEmergencyStop( void *oldStateData, struct event *event);

void Handle_EntrySafetyGuardHandling( void *oldStateData, struct event *event);
void Handle_EntrySafetyGuard( void *oldStateData, struct event *event);

void Handle_EntryPoweroff48V(void *oldStateData, struct event *event);
void Handle_EntryPowering48V(void *oldStateData, struct event *event);

void Handle_EntryControllerDisconnect(void *oldStateData, struct event *event);
void Handle_EntryControllerConnecting(void *oldStateData, struct event *event);
void Handle_EntryEtherCATError(void *oldStateData, struct event *event);
void Handle_EntryEtherCATResetting(void *oldStateData, struct event *event);

void Handle_EntryRobotOutofSafeSpace(void *oldStateData, struct event *event);
void Handle_EntryRobotCollisionStop(void *oldStateData, struct event *event);
void Handle_EntryRobotError(void *oldStateData, struct event *event);
void Handle_EntryRobotDisable(void *oldStateData, struct event *event);
void Handle_EntryRobotDisabling(void *oldStateData, struct event *event);
void Handle_EntryRobotEnabling(void *oldStateData, struct event *event);
void Handle_EntryRobotMoving(void *oldStateData, struct event *event);
void Handle_EntryRobotStopping(void *oldStateData, struct event *event);
void Handle_EntryRobotOpeningFreeDriver(void *oldStateData, struct event *event);
void Handle_EntryRobotClosingFreeDriver(void *oldStateData, struct event *event);
void Handle_EntryRobotFreeDriver(void *oldStateData, struct event *event);

void Handle_EntryRobotStandy( void *oldStateData, struct event *event );

//transition guard
//bool guard_RobotLoadCfg( const std::string& condition, struct event *event );

bool guard_BoxDisconnect( const std::string& condition, struct event *event );
bool guard_EmergencyStopHandling( const std::string& condition, struct event *event );
bool guard_EmergencyStop( const std::string& condition, struct event *event );
bool guard_Poweroff48V( const std::string& condition, struct event *event );
bool guard_SafetyGuard( const std::string& condition, struct event *event);
bool guard_SafetyGuardHandling( const std::string& condition, struct event *event);
bool guard_ControllerDisconnect( const std::string& condition, struct event *event );
bool guard_EtherCATError( const std::string& condition, struct event *event );
bool guard_RobotOutofSafeSpace( const std::string& condition, struct event *event );
bool guard_RobotCollisionStop( const std::string& condition, struct event *event );
bool guard_RobotError( const std::string& condition, struct event *event );
bool guard_RobotDisable( const std::string& condition, struct event *event );
bool guard_RobotEnabling( const std::string& condition, struct event *event );
bool guard_RobotStopping( const std::string& condition, struct event *event);
bool guard_RobotMoving( const std::string& condition, struct event *event );
bool guard_RobotFreeDriver( const std::string& condition, struct event *event );
bool guard_RobotStandy( const std::string& condition, struct event *event );

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool guard_RobotResetEmergencyStop(const std::string& condition, struct event *event);
//bool guard_RobotResetSafetyGuard(const std::string& condition, struct event *event);
//bool guard_RobotElectrify(const std::string& condition, struct event *event);

#ifdef __cplusplus
}
#endif

#endif


