
#include "hrc_if_xmlrpc_api.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_jsonLibrary/Json2xml.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

int web_read_cnt = 0;

namespace xmlrpcServer
{
    /*页面读取机器人实时状态*/
    xmlrpc_value * xmlrpc_ReadRealTimeInfo(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        string strJsonArea = "";

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        /*调试信息: 页面实时状态读取计数器+1*/
        web_read_cnt++;
        
        HMRC_Status_ReadRealTimeStatus(nRbtID, strJsonArea);
        xmlrpc_value* ret_value = xmlrpc_build_value(envP, "s", strJsonArea.c_str());
        static int printCount = 0;
        ++printCount;
        if(printCount>100)
        {
            printCount=0;
            //center_trace(center_log_debug, "\n%s\n\n",strJsonArea.c_str());
        }
        return ret_value;

    }

    /* TCP标定: 三点标定计算 */
    xmlrpc_value * xmlrpc_TCP3PointCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        center_trace(center_log_debug, "before xmlrpc_TCP3PointCalculate");

        string sCmd = "PointCalculate";
        string sJson = "";
        char* pName = nullptr;
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID , &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }        
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }
        double drPoint[24] = { 0 };

        center_trace(center_log_debug, "............xmlrpc_TCP3PointCalculate :%s\n",sJson.c_str());
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
            
        double drRet[6] = { 0 };
        int nQuality = 0;
        int nResult = HMRC_Status_TCPPositionCalculate_3P(
            &drPoint[0]/*len=6*/, &drPoint[6]/*len=6*/, &drPoint[12]/*len=6*/,
            drRet, nQuality);
        if(nResult!=REC_Successed)
            return xmlrpc_build_value(envP, "s", "error");

        center_trace(center_log_debug, "in point1 [%f,%f,%f,%f,%f,%f]",
            drPoint[0],drPoint[1],drPoint[2],drPoint[3],drPoint[4],drPoint[5]);

        center_trace(center_log_debug, "in point2 [%f,%f,%f,%f,%f,%f]",
            drPoint[6],drPoint[7],drPoint[8],drPoint[9],drPoint[10],drPoint[11]);

        center_trace(center_log_debug, "in point3 [%f,%f,%f,%f,%f,%f]",
            drPoint[12],drPoint[13],drPoint[14],drPoint[15],drPoint[16],drPoint[17]);

        center_trace(center_log_debug, "out point [%f,%f,%f,%f,%f,%f],[%d]",
            drRet[0],drRet[1],drRet[2],drRet[3],drRet[4],drRet[5],nQuality);


        string sRet = createJson(drRet);
        sRet = PointCalculateJson(sRet, nQuality);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }

    /* TCP标定: 四点标定计算 */
    xmlrpc_value * xmlrpc_TCPPositionCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        string sCmd = "PositionCalculate";
        string sJson = "";
        char* pName = nullptr;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }        
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        
        double drRet[6] = { 0 };
        int nQuality = 0;
        int erroPointIndex[4] = {0};
        int nResult = HMRC_Status_TCPPositionCalculate_4P(
            &drPoint[0]/*len=6*/, &drPoint[6]/*len=6*/, &drPoint[12]/*len=6*/, &drPoint[18],
            drRet, nQuality, erroPointIndex);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");
        center_trace(center_log_debug, "in point1 [%f, %f, %f, %f, %f, %f]",
            drPoint[0],drPoint[1],drPoint[2],drPoint[3],drPoint[4],drPoint[5]);
        
        center_trace(center_log_debug, "in point2 [%f, %f, %f, %f, %f, %f]",
            drPoint[6],drPoint[7],drPoint[8],drPoint[9],drPoint[10],drPoint[11]);
        
        center_trace(center_log_debug, "in point3 [%f, %f, %f, %f, %f, %f]",
            drPoint[12],drPoint[13],drPoint[14],drPoint[15],drPoint[16],drPoint[17]);

        center_trace(center_log_debug, "in point4 [%f, %f, %f, %f, %f, %f]",
            drPoint[18],drPoint[19],drPoint[20],drPoint[21],drPoint[22],drPoint[23]);
     
        center_trace(center_log_debug, "out point [%f,%f,%f,%f,%f,%f],[%d,%d,%d,%d]",
            drRet[0],drRet[1],drRet[2],drRet[3],drRet[4],drRet[5],
            erroPointIndex[0],erroPointIndex[1],erroPointIndex[2],erroPointIndex[3],
            nQuality);



        string sRet = createJson(drRet);
        sRet = PositionCalculateJson(sRet,nQuality,erroPointIndex);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }


    /* TCP标定: 方向计算 */
    xmlrpc_value * xmlrpc_TCPOrientationCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        string sCmd = "OrientationCalculate";
        string sJson = "";
        char* pName = nullptr;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID,&nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }        
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        double drRet[3] = { 0 };
        int nResult = HMRC_Status_TCPOrientationCalculate_2(
            &drPoint[6]/*len=6*/, &drPoint[0],
            drRet[0], drRet[1], drRet[2]);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");

        center_trace(center_log_debug, "in point1 [%f, %f, %f, %f, %f, %f]",
            drPoint[0],drPoint[1],drPoint[2],drPoint[3],drPoint[4],drPoint[5]);
        
        center_trace(center_log_debug, "in point2 [%f, %f, %f, %f, %f, %f]",
            drPoint[6],drPoint[7],drPoint[8],drPoint[9],drPoint[10],drPoint[11]);
        
        center_trace(center_log_debug, "out point [%f, %f, %f]",
            drRet[0],drRet[1],drRet[2]);



        string sOrien = OrientationCalculateJson(drRet);
        return xmlrpc_build_value(envP, "s", sOrien.c_str());
    }

    /* 用户坐标标定: 点 */
    xmlrpc_value * xmlrpc_UserPointCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        string sCmd = "PointCoordinate";
        string sJson = "";
        char* pName = nullptr;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }        
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }

        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        double drRet[6] = { 0 };
        int nResult = HMRC_Status_UserPointCoordinateCalculate(&drPoint[0], drRet);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");
        center_trace(center_log_debug,"ret [%f,%f,%f,%f,%f,%f]",
                drRet[0],drRet[1],drRet[2],drRet[3],drRet[4],drRet[5]);


        string sRet = createJson(drRet);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }


    /* 用户坐标标定: 线 */
    xmlrpc_value * xmlrpc_UserLineCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        string sCmd = "LineCoordinate";
        xmlrpc_int nClientType = 0;
        string sJson = "";
        char* pName = nullptr;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }

        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        double drRet[6] = { 0 };
        int nResult = HMRC_Status_UserLineCoordinateCalculate(
            &drPoint[0]/*len=6*/, &drPoint[6],
            drRet);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");

        center_trace(center_log_debug,"ret [%f,%f,%f,%f,%f,%f]",
                drRet[0],drRet[1],drRet[2],drRet[3],drRet[4],drRet[5]);
        string sRet = createJson(drRet);
        
        return xmlrpc_build_value(envP, "s", sRet.c_str());

    }

    /* 用户坐标标定: 面 */
    xmlrpc_value * xmlrpc_UserPlaneCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        string sCmd = "PlaneCoordinate";
        string sJson = "";
        char* pName = nullptr;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID,  &nClientType , &pName);
         if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }       
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmd, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        double drRet[6] = { 0 };
        int nResult = HMRC_Status_UserPlaneCoordinateCalculate(
            &drPoint[0]/*len=6*/, &drPoint[6], &drPoint[12],
            drRet);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");
        center_trace(center_log_debug,"ret [%f,%f,%f,%f,%f,%f]",
                drRet[0],drRet[1],drRet[2],drRet[3],drRet[4],drRet[5]);

        string sRet = createJson(drRet);
        return xmlrpc_build_value(envP, "s", sRet.c_str());

    }

    /* 是否是模拟机器人 */
    xmlrpc_value * xmlrpc_IsSimulation(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)

    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(ii)",  &nRbtID , &nClientType );
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }        
        xmlrpc_int nRet = HRC_GET_RM()->IsSimulation();
        return xmlrpc_build_value(envP, "i", nRet);
    }

    /* 读取机器人ID */
    xmlrpc_value * xmlrpc_ReadRobotID(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_3PARAMTER(paramArray,serInfo,channelInfo);

        string strRobotsInfo = "";
        HMRC_Status_ReadRobotsInfo(strRobotsInfo);

        return xmlrpc_build_value(envP, "s", strRobotsInfo.c_str());
    }

    /* 坐标计算pcs2acs */
    xmlrpc_value * xmlrpc_PCS2ACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        center_trace(center_log_debug, "before xmlrpc_PCS2ACS");

        string sJson = "";
        char* pName = nullptr;
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }

        PointCoord BaseCoord;
        PointCoord RawACSCoord;
        PointCoord TargetTCPCoord;
        PointCoord TargetUCSCoord;
        PointCoord TargetAcs;

        string sCmdBaseTcp = "BaseTCP";
        string sCmdTcp = "TCP";
        string sCmdAcs = "ACS";
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmdBaseTcp, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        BaseCoord.Axis[0] = drPoint[0];
        BaseCoord.Axis[1] = drPoint[1];
        BaseCoord.Axis[2] = drPoint[2];
        BaseCoord.Axis[3] = drPoint[3];
        BaseCoord.Axis[4] = drPoint[4];
        BaseCoord.Axis[5] = drPoint[5];

        if(getValue4Json(sJson, sCmdTcp, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        TargetTCPCoord.Axis[0] = drPoint[0];
        TargetTCPCoord.Axis[1] = drPoint[1];
        TargetTCPCoord.Axis[2] = drPoint[2];
        TargetTCPCoord.Axis[3] = drPoint[3];
        TargetTCPCoord.Axis[4] = drPoint[4];
        TargetTCPCoord.Axis[5] = drPoint[5];

        if(getValue4JsonJoint(sJson, sCmdAcs, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        RawACSCoord.Axis[0] = drPoint[0];
        RawACSCoord.Axis[1] = drPoint[1];
        RawACSCoord.Axis[2] = drPoint[2];
        RawACSCoord.Axis[3] = drPoint[3];
        RawACSCoord.Axis[4] = drPoint[4];
        RawACSCoord.Axis[5] = drPoint[5];

        TargetUCSCoord.Axis[0] = 0;
        TargetUCSCoord.Axis[1] = 0;
        TargetUCSCoord.Axis[2] = 0;
        TargetUCSCoord.Axis[3] = 0;
        TargetUCSCoord.Axis[4] = 0;
        TargetUCSCoord.Axis[5] = 0;

        center_trace(center_log_debug, "BaseCoord ACS[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     BaseCoord.Axis[0],BaseCoord.Axis[1],BaseCoord.Axis[2],
                     BaseCoord.Axis[3],BaseCoord.Axis[4],BaseCoord.Axis[5]);
        center_trace(center_log_debug, "RawACSCoord ACS[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     RawACSCoord.Axis[0],RawACSCoord.Axis[1],RawACSCoord.Axis[2],
                     RawACSCoord.Axis[3],RawACSCoord.Axis[4],RawACSCoord.Axis[5]);
        center_trace(center_log_debug, "TargetTCPCoord ACS[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     TargetTCPCoord.Axis[0],TargetTCPCoord.Axis[1],TargetTCPCoord.Axis[2],
                     TargetTCPCoord.Axis[3],TargetTCPCoord.Axis[4],TargetTCPCoord.Axis[5]);
        int nResult = HRC_GET_RM()->PCS2ACS(BaseCoord,TargetTCPCoord,TargetUCSCoord,RawACSCoord,TargetAcs);
        if(nResult!=REC_Successed)
            return xmlrpc_build_value(envP, "s", "error");
        double drRet[Max_ActualAxisCnt]={ TargetAcs.Axis[0],TargetAcs.Axis[1],TargetAcs.Axis[2],
                                        TargetAcs.Axis[3],TargetAcs.Axis[4],TargetAcs.Axis[5] };
        center_trace(center_log_debug, "TargetAcs ACS[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     TargetAcs.Axis[0],TargetAcs.Axis[1],TargetAcs.Axis[2],
                     TargetAcs.Axis[3],TargetAcs.Axis[4],TargetAcs.Axis[5]);
        string sRet = createJsonJoint(drRet);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }

    /* 坐标计算base坐标转为UcsTcp */
    xmlrpc_value * xmlrpc_Base2UcsTcp(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        center_trace(center_log_debug, "before Base2BaseTcp");

        string sJson = "";
        char* pName = nullptr;
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }

        PointCoord BaseCoord;
        PointCoord TcpCoord;
        PointCoord UcsCoord;
        PointCoord UcsTcpCoord;

        string sCmdBase = "Base";
        string sCmdTcp = "TCP";
        string sCmdUcs = "UCS";
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmdBase, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        BaseCoord.Axis[0] = drPoint[0];
        BaseCoord.Axis[1] = drPoint[1];
        BaseCoord.Axis[2] = drPoint[2];
        BaseCoord.Axis[3] = drPoint[3];
        BaseCoord.Axis[4] = drPoint[4];
        BaseCoord.Axis[5] = drPoint[5];

        if(getValue4Json(sJson, sCmdTcp, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        TcpCoord.Axis[0] = drPoint[0];
        TcpCoord.Axis[1] = drPoint[1];
        TcpCoord.Axis[2] = drPoint[2];
        TcpCoord.Axis[3] = drPoint[3];
        TcpCoord.Axis[4] = drPoint[4];
        TcpCoord.Axis[5] = drPoint[5];

        if(getValue4Json(sJson, sCmdUcs, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        UcsCoord.Axis[0] = drPoint[0];
        UcsCoord.Axis[1] = drPoint[1];
        UcsCoord.Axis[2] = drPoint[2];
        UcsCoord.Axis[3] = drPoint[3];
        UcsCoord.Axis[4] = drPoint[4];
        UcsCoord.Axis[5] = drPoint[5];

        int nResult = HRC_GET_RM()->Base2UcsTcp(BaseCoord,TcpCoord,UcsCoord,UcsTcpCoord);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");
        double drRet[Max_ActualAxisCnt]={ UcsTcpCoord.Axis[0],UcsTcpCoord.Axis[1],UcsTcpCoord.Axis[2],
                                        UcsTcpCoord.Axis[3],UcsTcpCoord.Axis[4],UcsTcpCoord.Axis[5] };
        /*center_trace(center_log_debug, "BaseCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     BaseCoord.Axis[0],BaseCoord.Axis[1],BaseCoord.Axis[2],
                     BaseCoord.Axis[3],BaseCoord.Axis[4],BaseCoord.Axis[5]);
        center_trace(center_log_debug, "TcpCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     TcpCoord.Axis[0],TcpCoord.Axis[1],TcpCoord.Axis[2],
                     TcpCoord.Axis[3],TcpCoord.Axis[4],TcpCoord.Axis[5]);
        center_trace(center_log_debug, "UcsCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     UcsCoord.Axis[0],UcsCoord.Axis[1],UcsCoord.Axis[2],
                     UcsCoord.Axis[3],UcsCoord.Axis[4],UcsCoord.Axis[5]);
        center_trace(center_log_debug, "UcsTcpCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     UcsTcpCoord.Axis[0],UcsTcpCoord.Axis[1],UcsTcpCoord.Axis[2],
                     UcsTcpCoord.Axis[3],UcsTcpCoord.Axis[4],UcsTcpCoord.Axis[5]);*/
        string sRet = createJson(drRet);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }
    /* 坐标计算base坐标转为UcsTcp */
    xmlrpc_value * xmlrpc_UcsTcp2Base(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        center_trace(center_log_debug, "before Base2BaseTcp");

        string sJson = "";
        char* pName = nullptr;
        xmlrpc_decompose_value(envP, paramArray, "(iis)",&nRbtID, &nClientType , &pName);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        if (nullptr != pName)
        {
            sJson = pName;
            free(pName);
        }

        PointCoord BaseCoord;
        PointCoord TcpCoord;
        PointCoord UcsCoord;
        PointCoord UcsTcpCoord;

        string sCmdUcsTcp = "UcsTcp";
        string sCmdTcp = "TCP";
        string sCmdUcs = "UCS";
        double drPoint[24] = { 0 };
        if(getValue4Json(sJson, sCmdUcsTcp, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }

        UcsTcpCoord.Axis[0] = drPoint[0];
        UcsTcpCoord.Axis[1] = drPoint[1];
        UcsTcpCoord.Axis[2] = drPoint[2];
        UcsTcpCoord.Axis[3] = drPoint[3];
        UcsTcpCoord.Axis[4] = drPoint[4];
        UcsTcpCoord.Axis[5] = drPoint[5];

        if(getValue4Json(sJson, sCmdTcp, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        TcpCoord.Axis[0] = drPoint[0];
        TcpCoord.Axis[1] = drPoint[1];
        TcpCoord.Axis[2] = drPoint[2];
        TcpCoord.Axis[3] = drPoint[3];
        TcpCoord.Axis[4] = drPoint[4];
        TcpCoord.Axis[5] = drPoint[5];

        if(getValue4Json(sJson, sCmdUcs, drPoint) != 0)
        {
            return xmlrpc_build_value(envP, "s", "error");
        }
        UcsCoord.Axis[0] = drPoint[0];
        UcsCoord.Axis[1] = drPoint[1];
        UcsCoord.Axis[2] = drPoint[2];
        UcsCoord.Axis[3] = drPoint[3];
        UcsCoord.Axis[4] = drPoint[4];
        UcsCoord.Axis[5] = drPoint[5];

        int nResult = HRC_GET_RM()->UcsTcp2Base(UcsTcpCoord,TcpCoord,UcsCoord,BaseCoord);
        if(nResult != REC_Successed)
             return xmlrpc_build_value(envP, "s", "error");
        double drRet[Max_ActualAxisCnt]={ BaseCoord.Axis[0],BaseCoord.Axis[1],BaseCoord.Axis[2],
                                        BaseCoord.Axis[3],BaseCoord.Axis[4],BaseCoord.Axis[5] };
        /*center_trace(center_log_debug, "UcsTcpCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     UcsTcpCoord.Axis[0],UcsTcpCoord.Axis[1],UcsTcpCoord.Axis[2],
                     UcsTcpCoord.Axis[3],UcsTcpCoord.Axis[4],UcsTcpCoord.Axis[5]);
        center_trace(center_log_debug, "TcpCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     TcpCoord.Axis[0],TcpCoord.Axis[1],TcpCoord.Axis[2],
                     TcpCoord.Axis[3],TcpCoord.Axis[4],TcpCoord.Axis[5]);
        center_trace(center_log_debug, "UcsCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     UcsCoord.Axis[0],UcsCoord.Axis[1],UcsCoord.Axis[2],
                     UcsCoord.Axis[3],UcsCoord.Axis[4],UcsCoord.Axis[5]);
        center_trace(center_log_debug, "BaseCoord[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f]\n",
                     BaseCoord.Axis[0],BaseCoord.Axis[1],BaseCoord.Axis[2],
                     BaseCoord.Axis[3],BaseCoord.Axis[4],BaseCoord.Axis[5]);*/
        string sRet = createJson(drRet);
        return xmlrpc_build_value(envP, "s", sRet.c_str());
    }
}
