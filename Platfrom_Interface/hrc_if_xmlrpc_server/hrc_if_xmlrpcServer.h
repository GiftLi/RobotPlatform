#pragma once

#include "hrc_if_xmlrpc_api.h"

namespace xmlrpcServer
{

    class HRDCS_xmlrpcServer
    {
    public:
    	static HRDCS_xmlrpcServer* Instance();
    public:
    	HRDCS_xmlrpcServer();
    	~HRDCS_xmlrpcServer();

    	int InitServer(int nPort);
    	int DeInitServer();

    private:
        int StartServer(const char *log_file_name, int nPort);
    	void RegsiterFunction(const char *methodName, xmlrpc_method2 methodFunction);
    	void RegsiterFunction();

        static void*  HRDCS_xmlrpcServer_work(void* pVoid);
    	static HRDCS_xmlrpcServer* m_instance;

    	static xmlrpc_server_abyss_parms m_serverparm;
    	static xmlrpc_env m_env;
    	static xmlrpc_registry * m_registryP;
    };
}

