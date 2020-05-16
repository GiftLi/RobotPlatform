#ifndef HRC_IF_XMLRPC_API_H
#define HRC_IF_XMLRPC_API_H


#include "hrc_if_xmlrpc_move_api.h"
#include "hrc_if_xmlrpc_setRobot_api.h"
#include "hrc_if_xmlrpc_setIO_api.h"
#include "hrc_if_xmlrpc_setConfig_api.h"
#include "hrc_if_xmlrpc_readRobot_api.h"
#include "hrc_if_xmlrpc_readIO_api.h"
#include "hrc_if_xmlrpc_readConfig_api.h"
#include "hrc_if_xmlrpc_script.h"
#include "hrc_if_xmlrpc_modbus_api.h"

#include "HRC_Public/hrc_public_log/hrc_public_log.h"

/* 只带默认两个参数的指令 */
#define DoRobotParame(x)\
    do{\
        try{\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParame fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)


/* 短点动 */
#define DoRobotParameShortMove(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_int nAxisID = 0;\
            xmlrpc_int nDirection = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(iiii)", &nRbtID, &nClientType, &nAxisID, &nDirection);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nAxisID, nDirection, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMouseMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* 长点动 */
#define DoRobotParameLongMove(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_int nAxisID = 0;\
            xmlrpc_int nDirection = 0;\
            xmlrpc_int nState = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(iiiii)",\
                    &nRbtID, &nClientType, &nAxisID, &nDirection, &nState);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nAxisID, nDirection,nState, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMouseMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

        

/* RealMove */
#define DoRobotParameRealMove(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_int nAxisID = 0;\
            xmlrpc_int nDirection = 0;\
            char * strDis=nullptr;\
            double dDistance = 0.0;\
            xmlrpc_decompose_value(envP, paramArray, "(iiiis)", &nRbtID, &nClientType, &nAxisID, &nDirection, &strDis);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            if (nullptr != strDis)\
            {\
                dDistance = atof(strDis);\
                free(strDis);\
            }\
            xmlrpc_int nRet = x(nRbtID, nAxisID, nDirection, dDistance, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMouseMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* Move */
#define DoRobotParameMove(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            PointCoord coord;\
            xmlrpc_decompose_value(envP, paramArray, "(iidddddd)", &nRbtID,&nClientType,\
                &(coord.Axis[0]), &(coord.Axis[1]), &(coord.Axis[2]),\
                &(coord.Axis[3]), &(coord.Axis[4]), &(coord.Axis[5]));\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, coord, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* MoveToPcs */
#define DoRobotParameMoveLTo(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            PointCoord coord;\
            string strTcp="";\
            string strUcs="";\
            char* pTcpName = nullptr;\
            char* pUcsName = nullptr;\
            xmlrpc_decompose_value(envP, paramArray, "(iiddddddss)", &nRbtID,&nClientType,\
                &(coord.Axis[0]), &(coord.Axis[1]), &(coord.Axis[2]),\
                &(coord.Axis[3]), &(coord.Axis[4]), &(coord.Axis[5]),\
                &pTcpName,&pUcsName);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            if (nullptr != pTcpName)\
            {\
                strTcp = pTcpName;\
                free(pTcpName);\
            }\
            if (nullptr != pUcsName)\
            {\
                strUcs = pUcsName;\
                free(pUcsName);\
            }\
            xmlrpc_int nRet = x(nRbtID, coord, strTcp,strUcs,nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* Move */
#define DoRobotParameMoveToSS(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            PointCoord coord;\
            xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* Long Move Event */
#define DoRobotParameLongMoveEvent(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

/* 传入json配置文件*/
#define DoRobotParameSetJsonConfig(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientID = 0;\
            cJSON * cJson = nullptr;\
            char* strJson = NULL;\
            xmlrpc_decompose_value(envP, paramArray, "(iis)", &nRbtID, &nClientID, &strJson);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            if (nullptr == strJson)\
            {\
                center_trace(center_log_error, "null json str");\
                return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
            }\
            if((cJson = cJSON_Parse(strJson))== nullptr)\
            {\
                center_trace(center_log_error, "error json str");\
                free(strJson);return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
            }\
            center_long_trace(center_log_debug, "%s", strJson);\
            xmlrpc_int nRet = x(nRbtID,cJson, nClientID);\
            free(strJson);\
            cJSON_Delete(cJson);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameSetConfig fail");\
            return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
        }\
    }while(0)

/* modification 传入json配置文件*/
#define DoRobotParameModifiJsonConfig(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientID = 0;\
            cJSON * cJson = nullptr;\
            char* strName  = NULL;\
            char* strJson = NULL;\
            xmlrpc_decompose_value(envP, paramArray, "(iiss)", &nRbtID, &nClientID,&strName, &strJson);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            if (nullptr == strJson )\
            {\
                center_trace(center_log_error, "null json str");\
                return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
            }\
            if (nullptr == strName )\
            {\
                center_trace(center_log_error, "null device name str");\
                return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
            }\
            if((cJson = cJSON_Parse(strJson))== nullptr)\
            {\
                center_trace(center_log_error, "error json str");\
                free(strJson);return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
            }\
            center_long_trace(center_log_debug, "%s", strJson);\
            xmlrpc_int nRet = x(nRbtID,strName,cJson, nClientID);\
            free(strJson);\
            free(strName);\
            cJSON_Delete(cJson);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameModifiJsonConfig fail");\
            return xmlrpc_build_value(envP, "i", REC_JsonFormatErr);\
        }\
    }while(0)



        
/* setio */
#define DoRobotParameSetDOState(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd SETIO ");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_int np1 = 0;\
            xmlrpc_int np2 = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(iiii)", &nRbtID, &nClientType, &np1, &np2);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, np1, np2);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParameMouseMove fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

#define DoRobotScriptParame(x)\
    do{\
        try{\
            center_trace(center_log_debug, "recv xmlrpc cmd");\
            xmlrpc_int nRbtID = 0;\
            xmlrpc_int nClientType = 0;\
            xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);\
            if (envP->fault_occurred)\
            {\
                center_trace(center_log_error, "xmlrpc call error %d %s",\
                    envP->fault_code,envP->fault_string);\
                return nullptr;\
            }\
            xmlrpc_int nRet = x(nRbtID, nClientType);\
            return xmlrpc_build_value(envP, "i", nRet);\
        }\
        catch(...)\
        {\
            center_trace(center_log_error, "DoRobotParame fail");\
            return xmlrpc_build_value(envP, "i", REC_CCCrash);\
        }\
    }while(0)

#endif
