

#include <unistd.h>
#include <iostream>
using namespace std;

#include "HRStatus_guard.h"
#include "HR_RobotAgent.h"

//void Handle_EntryLoadConfig( void *oldStateData, struct event *event)
//{
//    cout<<"Entry Load Config Statu."<<endl;
//    HRRbtAgentObj->LoadConfig();
//}
void Handle_EntryInitialize(void *oldStateData, struct event *event)
{
    cout<<"Entry Initialize Statu."<<endl;
    
    HRRbtAgentObj->ConnectToController();
    
}
void Handle_EntryReseting(void *oldStateData, struct event *event)
{
    cout<<"Entry Reseting Statu."<<endl;
}

void Handle_EntryElectricBoxDisconnect( void *oldStateData, struct event *event)
{
    cout<<"Entry ElectricBox Disconnect Statu."<<endl;
}
void Handle_EntryEmergencyStopHandling( void *oldStateData, struct event *event)
{
    cout<<"Entry EmergencyStop Handling Statu."<<endl;
    HRRbtAgentObj->EntryEmergencyStopHandling();
}
void Handle_EntryEmergencyStop( void *oldStateData, struct event *event)
{
    cout<<"Entry EmergencyStop Statu."<<endl;
}
void Handle_EntrySafetyGuardHandling( void *oldStateData, struct event *event)
{
    cout<<"Entry SafetyGuard Handling Statu."<<endl;
}
void Handle_EntrySafetyGuard( void *oldStateData, struct event *event)
{
    cout<<"Entry SafetyGuard Statu."<<endl;
}
void Handle_EntryPoweroff48V( void *oldStateData, struct event *event)
{
    cout<<"Entry Power off 48V Statu."<<endl;
}
void Handle_EntryPowering48V(void *oldStateData, struct event *event)
{
    cout<<"Entry Powering 48V Statu."<<endl;
}

void Handle_EntryControllerDisconnect(void *oldStateData, struct event *event)
{
    cout<<"Entry Controller Disconnect Statu."<<endl;
}
void Handle_EntryControllerConnecting(void *oldStateData, struct event *event)
{
    cout<<"Entry Controller Connecting Statu."<<endl;
}
void Handle_EntryEtherCATError(void *oldStateData, struct event *event)
{
    cout<<"Entry EtherCAT Error Statu."<<endl;
}
void Handle_EntryEtherCATResetting(void *oldStateData, struct event *event)
{
    cout<<"Entry EtherCAT Resetting Statu."<<endl;
}

void Handle_EntryRobotOutofSafeSpace(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot OutofSafeSpace Statu."<<endl;
}
void Handle_EntryRobotCollisionStop(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot CollisionStop Statu."<<endl;
}
void Handle_EntryRobotError(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Error Statu."<<endl;
}
void Handle_EntryRobotDisable(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Disabled Statu."<<endl;
}
void Handle_EntryRobotDisabling(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Disabling Statu."<<endl;
}
void Handle_EntryRobotEnabling(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Enabling Statu."<<endl;
}
void Handle_EntryRobotMoving(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Moving Statu."<<endl;
}
void Handle_EntryRobotStopping(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Stopping Statu."<<endl;
}
void Handle_EntryRobotOpeningFreeDriver(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Opening FreeDriver Statu."<<endl;
}
void Handle_EntryRobotClosingFreeDriver(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Closing FreeDriver Statu."<<endl;
}
void Handle_EntryRobotFreeDriver(void *oldStateData, struct event *event)
{
    cout<<"Entry Robot FreeDriver Statu."<<endl;
}

void Handle_EntryRobotStandy( void *oldStateData, struct event *event)
{
    cout<<"Entry Robot Standy Statu."<<endl;
}

//transition guard
//bool guard_RobotLoadCfg( const std::string& condition, struct event *event )
//{
//   return condition == event->cmd;
//}

bool guard_BoxDisconnect( const std::string& condition, struct event *event )
{
    //cout<<"guard BoxDisconnect."<<endl;
    return !HRRbtAgentObj->IsConnectToBox();
}
bool guard_EmergencyStopHandling( const std::string& condition, struct event *event )
{
    //cout<<"guard EmergencyStop Handling."<<endl;
    return HRRbtAgentObj->IsFinishEmergencyStopHandle();
}
bool guard_EmergencyStop( const std::string& condition, struct event *event )
{
    //cout<<"guard EmergencyStop."<<endl;
    return false;
}

bool guard_Poweroff48V( const std::string& condition, struct event *event )
{
    //cout<<"guard Power off 48V."<<endl;
    return false;
}

bool guard_SafetyGuardHandling( const std::string& condition, struct event *event )
{
    //cout<<"guard SafetyGuard Handling."<<endl;
    return false;
}
bool guard_SafetyGuard( const std::string& condition, struct event *event )
{
    //cout<<"guard SafetyGuard."<<endl;
    return false;
}

bool guard_ControllerDisconnect( const std::string& condition, struct event *event )
{
    //cout<<"guard Controller Disconnect."<<endl;
    return !HRRbtAgentObj->IsConnectController();
}
bool guard_EtherCATError( const std::string& condition, struct event *event )
{
    //cout<<"guard EtherCATError."<<endl;
    return HRRbtAgentObj->IsEtherCATError();
}
bool guard_RobotOutofSafeSpace( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Out of SafeSpace."<<endl;
    return HRRbtAgentObj->IsOutofSafeSpace();
}
bool guard_RobotCollisionStop( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot CollisionStop."<<endl;
    return HRRbtAgentObj->IsCollisionStop();
}
bool guard_RobotError( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Error."<<endl;
    return HRRbtAgentObj->IsError();
}
bool guard_RobotDisable( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Disable."<<endl;
    return HRRbtAgentObj->IsDisable();
}
bool guard_RobotEnabling( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Enabling."<<endl;
    return HRRbtAgentObj->IsEnabling();
}
bool guard_RobotMoving( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Moving."<<endl;
    return HRRbtAgentObj->IsMoving();
}
bool guard_RobotStopping( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Stopping."<<endl;
    return HRRbtAgentObj->IsStopping();
}
bool guard_RobotFreeDriver( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot FreeDriver."<<endl;
    return HRRbtAgentObj->IsFreeDriver();
}
bool guard_RobotStandy( const std::string& condition, struct event *event )
{
    //cout<<"guard Robot Standy."<<endl;
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

