#include "EleBoxFactory.h"

/*
 @ 创建2代电箱
*/
BaseEleBox* EleBoxV2Factory::createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)
{
	return new EleBoxV2(nDeviceID,strIp,nPort);
}

BaseEleBox* EleBoxV2Factory::createEleBoxInstance(const string strPath)
{
	return new EleBoxV2(strPath);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*
 @ 创建4代电箱
*/
BaseEleBox* EleBoxV4Factory::createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)
{
	return new EleBoxV4(nDeviceID,strIp,nPort);
}

BaseEleBox* EleBoxV4Factory::createEleBoxInstance(const string strPath)
{
	return new EleBoxV4(strPath);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*
 @ 创建模拟电箱
*/
BaseEleBox* EleBoxSimulationFactory::createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)
{
	return new EleBoxV4(nDeviceID,strIp,nPort);
}

BaseEleBox* EleBoxSimulationFactory::createEleBoxInstance(const string strPath)
{
	return new EleBoxV4(strPath);
}


#if 0
EleBoxFactory* EleBoxFactory::pEleBoxFactoryInstance = nullptr;
SaftLock EleBoxFactory::m_EleBox_factory_lock;

EleBoxFactory* EleBoxFactory::getEleBoxFactoryInstance()
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
	if(nullptr == pEleBoxFactoryInstance)
	{
		pEleBoxFactoryInstance = new EleBoxFactory();
	}
	
	return pEleBoxFactoryInstance;
	
}


BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,int nDeviceID,string strIp,int nPort)
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);

	switch(enVersion)
	{
		case en_EleBox_Type_V1:
			/* 返回1代电箱 */
		
			break;

		case en_EleBox_Type_V2:
			/* 返回2代电箱 */
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV2(nDeviceID,strIp,nPort);
			}
			
			break;

		case en_EleBox_Type_V3:
			/* 返回3代电箱 */
		
			break;

		case en_EleBox_Type_V4:
			/* 返回4代电箱 */
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(nDeviceID,strIp,nPort);
			}
			
			break;

		case en_EleBox_Type_Simulation:
			
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxSimulation(nDeviceID,strIp,nPort);
			}

			break;
			
		default:
			return nullptr;
	}

		return m_pEleBox;
}


BaseEleBox* EleBoxFactory::getEleBoxInstance(EN_EleBox_Type enVersion,string strPath)
{
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);

	switch(enVersion)
	{
		case en_EleBox_Type_V1:
			/* 返回1代电箱 */
		
			break;

		case en_EleBox_Type_V2:
			/* 返回2代电箱 */
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV2(strPath);
			}
			break;

		case en_EleBox_Type_V3:
			/* 返回3代电箱 */
		
			break;

		case en_EleBox_Type_V4:
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxV4(strPath);
			}

			break;

		case en_EleBox_Type_Simulation:
			if(nullptr == m_pEleBox)
			{
				m_pEleBox = new EleBoxSimulation(strPath);
			}

			break;

		default:
			return nullptr;
	}

	return m_pEleBox;
}

BaseEleBox* EleBoxFactory::getEleBoxInstance()
{
	
	AutoSaftMutex factoryLock(&m_EleBox_factory_lock);
			
	if(nullptr == m_pEleBox)
	{
		printf("please init Box by [INIT_ELEBOX_TCP_INSTANCE] or [INIT_ELEBOX_RTU_INSTANCE]\n");

		return nullptr;
	}
	
	return m_pEleBox;
}
#endif

//从INI文件读取字符串类型数据
string GetIniKeyString(string title,string key)
{
    FILE *fp;
    char szLine[1024];
    static char tmpstr[1024];
    int rtnval;
    int i = 0;
    int flag = 0;
    char *tmp;

    if((fp = fopen(FILE_PATH, "r")) == nullptr)
    {
        printf("have   no   such   file \n");
        return "";
    }
    while(!feof(fp))
    {
        rtnval = fgetc(fp);
        if(rtnval == EOF)
        {
            break;
        }
        else
        {
            szLine[i++] = rtnval;
        }
        if(rtnval == '\n')
        {
            szLine[--i] = '\0';
            i = 0;
            tmp = strchr(szLine, '=');

            if(( tmp != nullptr )&&(flag == 1))
            {
                if(strstr(szLine,key.c_str())!=nullptr)
                {
                    //注释行
                    if ('#' == szLine[0])
                    {
                    }
                    else if ( '/' == szLine[0] && '/' == szLine[1] )
                    {

                    }
                    else
                    {
                        //找打key对应变量
                        strcpy(tmpstr,tmp+1);
                        fclose(fp);
                        return tmpstr;
                    }
                }
            }
            else
            {
                strcpy(tmpstr,"[");
                strcat(tmpstr,title.c_str());
                strcat(tmpstr,"]");
                if( strncmp(tmpstr,szLine,strlen(tmpstr)) == 0 )
                {
                    //找到title
                    flag = 1;
                }
            }
        }
    }
    fclose(fp);
    return "";
}

//从INI文件读取整类型数据
int GetIniKeyInt(string title,string key)
{
    return atoi(GetIniKeyString(title,key).c_str());
}



