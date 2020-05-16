#include "hrc_if_xmlrpc_readIO_api.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"

namespace xmlrpcServer
{

    /*xmlrpc_value * xmlrpc_ReadElectricityBoxDI(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiiiiiii)",
            nRet,
            boxState.nDInputIO[0], boxState.nDInputIO[1], boxState.nDInputIO[2], boxState.nDInputIO[3],
            boxState.nDInputIO[4], boxState.nDInputIO[5], boxState.nDInputIO[6], boxState.nDInputIO[7]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxSI(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiiiiiii)",
            nRet,
            boxState.nSInputIO[0], boxState.nSInputIO[1], boxState.nSInputIO[2], boxState.nSInputIO[3],
            boxState.nSInputIO[4], boxState.nSInputIO[5], boxState.nSInputIO[6], boxState.nSInputIO[7]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxExternDI(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiii)",
            nRet,
            boxState.nExterInputIO[0], boxState.nExterInputIO[1],
            boxState.nExterInputIO[2], boxState.nExterInputIO[3]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiiiiiii)",
            nRet,
            boxState.nDOutputIO[0], boxState.nDOutputIO[1], boxState.nDOutputIO[2], boxState.nDOutputIO[3],
            boxState.nDOutputIO[4], boxState.nDOutputIO[5], boxState.nDOutputIO[6], boxState.nDOutputIO[7]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxSO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiiiiiii)",
            nRet,
            boxState.nSOutputIO[0], boxState.nSOutputIO[1], boxState.nSOutputIO[2], boxState.nSOutputIO[3],
            boxState.nSOutputIO[4], boxState.nSOutputIO[5], boxState.nSOutputIO[6], boxState.nSOutputIO[7]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxExternDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiiii)",
            nRet,
            boxState.nExterOutputIO[0], boxState.nExterOutputIO[1],
            boxState.nExterOutputIO[2], boxState.nExterOutputIO[3]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxAnalog(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iididdd)",
            nRet,
            boxState.stAnalogOutput[0].nAnalogMode, boxState.stAnalogOutput[0].dbAnalog,
            boxState.stAnalogOutput[1].nAnalogMode, boxState.stAnalogOutput[1].dbAnalog,
            boxState.dbAnalogInput[0], boxState.dbAnalogInput[1]);
    }
    xmlrpc_value * xmlrpc_ReadElectricityBoxPower(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        ST_ElectricityBoxInfo boxState = { 0 };
        int nRet = HMRC_Status_ReadElectricityBoxState(boxState);
        return xmlrpc_build_value(envP, "(iiddddd)",
            nRet, boxState.nRemotePoweroff,
            boxState.dbRobotSrcVoltage, boxState.dbRobotSupplyVoltage,
            boxState.dbRobotSupplyCurrent, boxState.dbIOVoltage, boxState.dbIOCurrent);
    }
    xmlrpc_value * xmlrpc_ReadRTRbtEndIO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
        ST_RbtRealTimeStatuV4 rbtState = { 0 };
        int nRet = HMRC_Status_ReadRobotRealTimeStatus(nRbtID, rbtState);
        return xmlrpc_build_value(envP, "(iiiiiiiiidd)",
            nRet,
            rbtState.nInDIO[0], rbtState.nInDIO[1], rbtState.nInDIO[2], rbtState.nInDIO[3],
            rbtState.nOutDIO[0], rbtState.nOutDIO[1], rbtState.nOutDIO[2], rbtState.nOutDIO[3],
            rbtState.dbAnalogInput[0], rbtState.dbAnalogInput[1]);
    }


    xmlrpc_value * xmlrpc_ReadRTRbtEndModbusBTN(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
        ST_RbtRealTimeStatuV4 rbtState = { 0 };
        int nRet = HMRC_Status_ReadRobotRealTimeStatus(nRbtID, rbtState);
        return xmlrpc_build_value(envP, "(iiiii)",
            nRet,
            rbtState.nModbusBTN[0], rbtState.nModbusBTN[1],
            rbtState.nModbusBTN[2], rbtState.nModbusBTN[3]);
    }*/

}

