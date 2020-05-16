#include "HR_FSM.h"

#include "HR_RobotAgent.h"

#include "HRStatus.h"
#include "HR_CmdMsg.h"


SaftLock HR_FSM::m_FSMLock;
int FSM_handleEvent( struct event *event )
{
    AutoSaftMutex FSMLocker(&HR_FSM::m_FSMLock);
    return stateM_handleEvent( &HRStatus::g_rbtfsm, event);
}

Build_Singleton(HR_FSM)

HR_FSM::HR_FSM(/* args */):m_strExeDir("")
{
    m_strTimerCmd.push_back(Cmd_CheckIs_BoxDisconnect);
    m_strTimerCmd.push_back(Cmd_CheckIs_EmergencyStopHandling);
    m_strTimerCmd.push_back(Cmd_CheckIs_EmergencyStop);
    m_strTimerCmd.push_back(Cmd_CheckIs_Poweroff48V);
    m_strTimerCmd.push_back(Cmd_CheckIs_SafetyGuardHandling);
    m_strTimerCmd.push_back(Cmd_CheckIs_SafetyGuard);
    m_strTimerCmd.push_back(Cmd_CheckIs_ControllerDisconnect);
    m_strTimerCmd.push_back(Cmd_CheckIs_EtherCATError);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotOutofSafeSpace);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotCollisionStop);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotError);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotDisable);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotEnabling);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotMoving);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotStopping);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotFreeDriver);
    m_strTimerCmd.push_back(Cmd_CheckIs_RobotStandy);
}

HR_FSM::~HR_FSM()
{
}

void HR_FSM::Initialize(const string& strExeDir)
{
    m_strExeDir=strExeDir;

    HRStatus::InitializeStatus();
    stateM_init( &HRStatus::g_rbtfsm, &HRStatus::state_LoadConfig, NULL );

    struct event ev = { Event_Msg,Cmd_RobotLoadCfg};
    FSM_handleEvent(&ev);
    //stateM_handleEvent( &HRStatus::g_rbtfsm,  &ev);
}

void HR_FSM::HandleMsg(const string&cmd,const vector<string>&param,vector<string>&result)
{
    struct event ev;
    ev.type = Event_Msg;
    ev.cmd = cmd;
    ev.param = param;
    FSM_handleEvent(&ev);
    //stateM_handleEvent( &HRStatus::g_rbtfsm, &ev );
    result = ev.result;
}
void HR_FSM::HandleTimer()
{
    struct event ev;
    ev.type = Event_Timer;
    ev.param.clear();

    int nFSMHandleRet = 0;
    std::size_t cmdCount = m_strTimerCmd.size();
    for(std::size_t i=0; i<cmdCount; ++i)
    {
        ev.cmd = m_strTimerCmd[i];
        nFSMHandleRet = FSM_handleEvent(&ev);
        //nFSMHandleRet = stateM_handleEvent( &HRStatus::g_rbtfsm, &ev );
        if (nFSMHandleRet!=stateM_noStateChange)
        {
            break;
        }
        
    }
    
}
