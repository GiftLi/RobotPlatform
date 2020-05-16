#ifndef HRC_IF_XMLRPC_SETCONFIG_API_H
#define HRC_IF_XMLRPC_SETCONFIG_API_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{

    /* ���õ������� */
    xmlrpc_value * xmlrpc_SetKinematicCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �����û����� */
    xmlrpc_value * xmlrpc_SetUserCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���û�����װ�Ƕ� */
    xmlrpc_value * xmlrpc_SetBaseMountingAngle(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ø��ز��� */
    xmlrpc_value * xmlrpc_SetPayload(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ÿռ������˶���Χ */
    xmlrpc_value * xmlrpc_SetPcsSafeSpaceLimit(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ùؽ������˶���Χ */
    xmlrpc_value * xmlrpc_SetAcsSafeSpaceLimit(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ð�ȫ�ȼ� */
    xmlrpc_value * xmlrpc_SetCollideLevel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �������ؽ��˶��ٶ� */
    xmlrpc_value * xmlrpc_SetMoveJointMotionLimits(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��������˶��ٶ� */        
    xmlrpc_value * xmlrpc_SetMovePcsMotionLimits(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �������ؽ��˶�ֹͣ�ٶ� */
    xmlrpc_value * xmlrpc_SetStopJointMotionLimits(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��������˶�ֹͣ�ٶ� */
    xmlrpc_value * xmlrpc_SetStopPcsMotionLimits(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ñ�������IO */
    xmlrpc_value * xmlrpc_SetEmergencyForResetIO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ñ�������IO״̬ */
    xmlrpc_value * xmlrpc_SetEmergencyForResetIOState(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ð�ȫ��Ļʹ�� */
    xmlrpc_value * xmlrpc_SetSafetyGuardMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ð�ȫ��Ļ��ʽ */
    xmlrpc_value * xmlrpc_SetSafetyGuardHold(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ð�ȫƽ�� */
    xmlrpc_value * xmlrpc_SetSafetyPanel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetEndDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetEndDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetEndAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetBoxAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetBoxAOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetBoxCIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetBoxCOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetBoxDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetBoxDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetRobotConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    xmlrpc_value * xmlrpc_SetRobotHardConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SaveScriptFile(xmlrpc_env* const envP,
            xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SaveRobotHardFile(xmlrpc_env* const envP,
            xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

/*
    xmlrpc_value * xmlrpc_SetStartFeedforwardMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetCloseFeedforwardMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    xmlrpc_value * xmlrpc_SetFeedforwardVelocityMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
*/


    /* modbus�豸 config*/
    xmlrpc_value * xmlrpc_AddModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_DelModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_SetModbusClientPamar(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);


}
#endif
