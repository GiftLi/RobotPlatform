#include "HRStatus_action.h"
#include "HR_RobotAgent.h"
#include "HR_Errorcode.h"
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;

bool action_LoadCfg(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Load config."<<endl;
    HRRbtAgentObj->LoadConfig();
    HRRbtAgentObj->ConnectToBox();
    
    return true;
}
bool action_ConnectToBox( void *oldStateData, struct event *event, void *newStateData )
{
    cout<<"action ConnectToBox."<<endl;
    HRRbtAgentObj->ConnectToBox();
    return true;
}
//void action_EmergencyStopHandling(void *oldStateData, struct event *event, void *newStateData)
//{
//    cout<<"action EmergencyStop Handling."<<endl;
//}
bool action_RobotResetEmergencyStop(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Reset EmergencyStop."<<endl;
    return true;
}
bool action_ConnectToController(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Connect to Controller."<<endl;
    HRRbtAgentObj->ConnectToController();
    return true;
}
bool action_RobotResetEtherCAT(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Reset EtherCAT."<<endl;
    return true;
}
bool action_RobotResetSafetyGuard(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Reset SafetyGuard."<<endl;
    return true;
}
bool action_RobotElectrify(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Electrify."<<endl;
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool action_RobotEnable(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Enable."<<endl;
    HRRbtAgentObj->RobotEnable(true);
    return true;
}
bool action_RobotDisable(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Disable."<<endl;
    HRRbtAgentObj->RobotEnable(false);
    return true;
}
bool action_RobotReset(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Reset."<<endl;
    HRRbtAgentObj->RobotReset();
    return true;
}
bool action_RobotStop(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Stop."<<endl;
    HRRbtAgentObj->RobotStop();
    return true;
}
bool action_RobotOpenFreeDriver(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Open FreeDriver."<<endl;
    return true;
}
bool action_RobotCloseFreeDriver(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Close FreeDriver."<<endl;
    return true;
}
bool action_RobotSetOverride(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action Set Override."<<endl;
    int nRet = REC_Successed;
    do
    {
        if (event==nullptr){nRet= REC_FormatError;break;}
        if (event->param.size() != 2){nRet= REC_FormatError;break;}

        int nRbtID = stoi(event->param[0]);
        double dbOverride = stof(event->param[1]);

        nRet = HRRbtAgentObj->SetOverride(nRbtID,dbOverride);
    } while (false);
    event->result.push_back(to_string(nRet));
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool action_RobotMoveToSS(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action MoveToSS."<<endl;
    return true;
}
bool action_RobotMoveJ(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action MoveJ."<<endl;
    int nRet = REC_Successed;
    do
    {
        if (event==nullptr){nRet= REC_FormatError;break;}
        if (event->param.size() != 7){nRet= REC_FormatError;break;}

        int nRbtID = stoi(event->param[0]);
        double Axis1 = stoi(event->param[1]);
        double Axis2 = stoi(event->param[2]);
        double Axis3 = stoi(event->param[3]);
        double Axis4 = stoi(event->param[4]);
        double Axis5 = stoi(event->param[5]);
        double Axis6 = stoi(event->param[6]);

        nRet = HRRbtAgentObj->Move_DirAcs(nRbtID,Axis1,Axis2,Axis3,Axis4,Axis5,Axis6);
    } while (false);
    event->result.push_back(to_string(nRet));
    return true;
}
bool action_RobotMoveL(void *oldStateData, struct event *event, void *newStateData)
{
    cout<<"action MoveL."<<endl;
    int nRet = REC_Successed;
    do
    {
        if (event==nullptr){nRet= REC_FormatError;break;}
        if (event->param.size() != 7){nRet= REC_FormatError;break;}

        int nRbtID = stoi(event->param[0]);
        double Axis1 = stoi(event->param[1]);
        double Axis2 = stoi(event->param[2]);
        double Axis3 = stoi(event->param[3]);
        double Axis4 = stoi(event->param[4]);
        double Axis5 = stoi(event->param[5]);
        double Axis6 = stoi(event->param[6]);

        nRet = HRRbtAgentObj->Move_LinePcs(nRbtID,Axis1,Axis2,Axis3,Axis4,Axis5,Axis6);
    } while (false);
    event->result.push_back(to_string(nRet));
    return true;
}

