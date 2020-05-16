#ifndef _HR_STATUS_H
#define _HR_STATUS_H

#include "stateMachine.h"
#include "HRStatus_action.h"
#include "HRStatus_guard.h"
#include "HR_CmdMsg.h"

/* Types of events */
enum eventType {
   Event_Msg=0,
   Event_Timer,
};

class HRStatus
{
private:
    /* data */
public:
    HRStatus(/* args */){}
    ~HRStatus(){}

static void InitializeStatus();

public:

static struct stateMachine g_rbtfsm;
//初始化状态
static struct state state_LoadConfig;
static struct state state_Initialize;
static struct state state_Reseting;
//电箱状态
static struct state state_ElectricBoxDisconnect;

//急停状态
static struct state state_EmergencyStopHandling;
static struct state state_EmergencyStop;

//48V供电状态
//static struct state state_Poweredby48V;
static struct state state_Powering48V;
static struct state state_Poweroff48V;

//安全光幕状态
static struct state state_SafetyGuardHandling;
static struct state state_SafetyGuard;

//控制器状态
static struct state state_ControllerDisconnect;
static struct state state_ControllerConnecting;
static struct state state_EtherCATError;
static struct state state_EtherCATResetting;

//机器人状态
static struct state state_RobotOutofSafeSpace;
static struct state state_RobotCollisionStop;
static struct state state_RobotError;
static struct state state_RobotDisable;
static struct state state_RobotDisabling;
static struct state state_RobotEnabling;
static struct state state_RobotMoving;
static struct state state_RobotStopping;
static struct state state_RobotOpeningFreeDriver;
static struct state state_RobotClosingFreeDriver;
static struct state state_RobotFreeDriver;
static struct state state_RobotStandy;

//外设状态
};
#endif


