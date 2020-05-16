#pragma once
#include <string>
#include "BaseEleBox.h"
#include "EleBoxV4.h"
#include "EleBoxV2.h"
#include "EleBoxSimulation.h"

#define FILE_PATH "/usr/local/etc/Motion/Box.ini"

string GetIniKeyString(string title,string key);
int GetIniKeyInt(string title,string key);



class EleBoxBaseFactory
{
public:
	EleBoxBaseFactory(){};
	virtual ~EleBoxBaseFactory(){};

	virtual BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort)=0;
	virtual BaseEleBox* createEleBoxInstance(const string strPath)=0;
};



class EleBoxV2Factory:public EleBoxBaseFactory
{
public:
	EleBoxV2Factory(){};
	virtual ~EleBoxV2Factory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);

};

class EleBoxV4Factory:public EleBoxBaseFactory
{
public:
	EleBoxV4Factory(){};
	virtual ~EleBoxV4Factory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);
};


class EleBoxSimulationFactory:public EleBoxBaseFactory
{
public:
	EleBoxSimulationFactory(){};
	virtual ~EleBoxSimulationFactory(){};

	BaseEleBox* createEleBoxInstance(const int nDeviceID,const string strIp,const int nPort);
	BaseEleBox* createEleBoxInstance(const string strPath);
};

