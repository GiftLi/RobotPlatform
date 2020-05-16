#ifndef HRC_IF_SERVER_API_H
#define HRC_IF_SERVER_API_H

#include <string>
#include <vector>

#include "HRC_Public/hrc_public_func.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "HRC_Public/hrc_public_log/hrc_public_log.h"

using namespace std;

namespace HRC_If_Server_Api
{
    int _GeneralRespones(string strCmd, int nRet, string& strResponse);

    /*setrobot*/
    int IF_Electrify(vector<string>& vcRequest, string& strResponse);
    int IF_Blackout(vector<string>& vcRequest, string& strResponse);
    int IF_StartMaster(vector<string>& vcRequest, string& strResponse);
    int IF_CloseMaster(vector<string>& vcRequest, string& strResponse);
    int IF_GrpPowerOff(vector<string>& vcRequest, string& strResponse);
    int IF_GrpPowerOn(vector<string>& vcRequest, string& strResponse);
    int IF_GrpReset(vector<string>& vcRequest, string& strResponse);
    int IF_ResetEStop(vector<string>& vcRequest, string& strResponse);
    int IF_ResetESGuard(vector<string>& vcRequest, string& strResponse);
    int IF_GrpStop(vector<string>& vcRequest, string& strResponse);
    int IF_GrpStopMoving(vector<string>& vcRequest, string& strResponse);
    int IF_GrpPause(vector<string>& vcRequest, string& strResponse);
    int IF_GrpContinue(vector<string>& vcRequest, string& strResponse);
    int IF_StartAssistiveMode(vector<string>& vcRequest, string& strResponse);
    int IF_CloseAssistiveMode(vector<string>& vcRequest, string& strResponse);
    int IF_SetOverride(vector<string>& vcRequest, string& strResponse);
    int IF_SetSimulation(vector<string>& vcRequest, string& strResponse);
    int IF_GrpSetBreakMode(vector<string>& vcRequest, string& strResponse);
    int IF_GrpSetSetHomeStep2(vector<string>& vcRequest, string& strResponse);
    int IF_GrpSetHomePositon(vector<string>& vcRequest, string& strResponse);


    /*setconfig*/
    int IF_ElfinHomeStep2(vector<string>& vcRequest, string& strResponse);
    int IF_EncoderSetHomeEndatPos(vector<string>& vcRequest, string& strResponse);
    int IF_SetTCPByName(vector<string>& vcRequest, string& strResponse);
    int IF_SetUCSByName(vector<string>& vcRequest, string& strResponse);
    int IF_SetCollideStopPayload(vector<string>& vcRequest, string& strResponse);
    int IF_SetMoveJointMotionLimits(vector<string>& vcRequest, string& strResponse);
    int IF_SetMovePcsMotionLimits(vector<string>& vcRequest, string& strResponse);
    int IF_SetStopJointMotionLimits(vector<string>& vcRequest, string& strResponse);
    int IF_SetStopPcsMotionLimits(vector<string>& vcRequest, string& strResponse);
    int IF_SetBaseMountingAngle(vector<string>& vcRequest, string& strResponse);
    int IF_SetToolCoordinateMotion(vector<string>& vcRequest, string& strResponse);
    int IF_SetCollisionStopMode(vector<string>& vcRequest, string& strResponse);
    int IF_SetCollisionMomentumThresholds(vector<string>& vcRequest, string& strResponse);

    int IF_SetSlaveType(vector<string>& vcRequest, string& strResponse);
    int IF_SetEndIOType(vector<string>& vcRequest, string& strResponse);
    int IF_SetEncodeType(vector<string>& vcRequest, string& strResponse);
    int IF_SetEncodeRatio(vector<string>& vcRequest, string& strResponse);
    int IF_SetGearRatio(vector<string>& vcRequest, string& strResponse);

    /*setio*/
    int IF_SetBoxDO(vector<string>& vcRequest, string& strResponse);
    int IF_SetBoxCO(vector<string>& vcRequest, string& strResponse);
    int IF_SetBoxAO(vector<string>& vcRequest, string& strResponse);
    int IF_SetBoxAOMode(vector<string>& vcRequest, string& strResponse);
    int IF_SetEndDO(vector<string>& vcRequest, string& strResponse);
    int IF_SetLEDColour(vector<string>& vcRequest, string& strResponse);

    /*set modbus*/
    int IF_SetModbusServerBit(vector<string>& vcRequest, string& strResponse);
    int IF_ReadModbusServerBit(vector<string>& vcRequest, string& strResponse);
     
    /*readrobot*/
    int IF_ReadActualPos(vector<string>& vcRequest, string& strResponse);
    int IF_ReadRobotPosInfo(vector<string>& vcRequest, string& strResponse);
    int IF_ReadOverride(vector<string>& vcRequest, string& strResponse);
    int IF_ReadRobotState(vector<string>& vcRequest, string& strResponse);
    int IF_ReadControlMode(vector<string>& vcRequest, string& strResponse);
    int IF_ReadCurEncode(vector<string>& vcRequest, string& strResponse);
    int IF_ReadRobotInfoParam(vector<string>& vcRequest, string& strResponse);

    int IF_ReadTCPByName(vector<string>& vcRequest, string& strResponse);
    int IF_ReadUCSByName(vector<string>& vcRequest, string& strResponse);
    int IF_ReadDefaultTCPName(vector<string>& vcRequest, string& strResponse);
    int IF_ReadDefaultUCSName(vector<string>& vcRequest, string& strResponse);

    /*coordinate translate*/
    int IF_Base2TCPUCS(vector<string>& vcRequest, string& strResponse);
    int IF_PCS2ACS(vector<string>& vcRequest, string& strResponse);
    /*readio*/
    int IF_ReadDI(vector<string>& vcRequest, string& strResponse);
    int IF_ReadDO(vector<string>& vcRequest, string& strResponse);
    int IF_ReadCI(vector<string>& vcRequest, string& strResponse);
    int IF_ReadCO(vector<string>& vcRequest, string& strResponse);
    int IF_ReadEI(vector<string>& vcRequest, string& strResponse);
    int IF_ReadEO(vector<string>& vcRequest, string& strResponse);
    int IF_ReadC1AO(vector<string>& vcRequest, string& strResponse);
    int IF_ReadC2AO(vector<string>& vcRequest, string& strResponse);
    int IF_ReadC1AI(vector<string>& vcRequest, string& strResponse);
    int IF_ReadC2AI(vector<string>& vcRequest, string& strResponse);
    int IF_ReadEAI1(vector<string>& vcRequest, string& strResponse);
    int IF_ReadEAI2(vector<string>& vcRequest, string& strResponse);

    
    /*int IF_ReadSerialAnalog(vector<string>& vcRequest, string& strResponse);
    int IF_ReadAnalogInput(vector<string>& vcRequest, string& strResponse);
    int IF_ReadInIOState(vector<string>& vcRequest, string& strResponse); 
    int IF_ReadControlInIOState(vector<string>& vcRequest, string& strResponse);
    int IF_ReadOutIOState(vector<string>& vcRequest, string& strResponse); 
    int IF_ReadMultiSerialDI(vector<string>& vcRequest, string& strResponse);*/


    /*readconfig*/
    int IF_ReadHomePosition(vector<string>& vcRequest, string& strResponse);

    /*move*/
    int IF_ShortJogJ(vector<string>& vcRequest, string& strResponse);
    int IF_ShortJogL(vector<string>& vcRequest, string& strResponse);
    int IF_LongJogJ(vector<string>& vcRequest, string& strResponse);
    int IF_LongJogL(vector<string>& vcRequest, string& strResponse);
    int IF_MoveJ(vector<string>& vcRequest, string& strResponse);
    int IF_MoveL(vector<string>& vcRequest, string& strResponse);
    int IF_MoveC(vector<string>& vcRequest, string& strResponse);
    int IF_MoveRelJ(vector<string>& vcRequest, string& strResponse);
    int IF_MoveRelL(vector<string>& vcRequest, string& strResponse);
    int IF_StartPushBlending(vector<string>& vcRequest, string& strResponse);
    int IF_PushBlendingPoint(vector<string>& vcRequest, string& strResponse);
    int IF_StartBlendingMotion(vector<string>& vcRequest, string& strResponse);
    int IF_WayPoint(vector<string>& vcRequest, string& strResponse);
    int IF_WayPointRel(vector<string>& vcRequest, string& strResponse);

    /*script control*/
    int IF_StartScript(vector<string>& vcRequest, string& strResponse);
    int IF_StopScript(vector<string>& vcRequest, string& strResponse);
    int IF_PauseScript(vector<string>& vcRequest, string& strResponse);
    int IF_ContinueScript(vector<string>& vcRequest, string& strResponse);
    int IF_NextStepScript(vector<string>& vcRequest, string& strResponse);
    int IF_NextBreakPoint(vector<string>& vcRequest, string& strResponse);
    int IF_RecvCmdID(vector<string>& vcRequest, string& strResponse);
    int IF_RecvVarValue(vector<string>& vcRequest, string& strResponse);
    int IF_RecvFinish(vector<string>& vcRequest, string& strResponse); 
    int IF_RecvScriptMsg(vector<string>& vcRequest, string& strResponse);
};
#endif
