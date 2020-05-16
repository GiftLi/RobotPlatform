#ifndef _HR_FSM_H
#define _HR_FSM_H

#include <vector>
#include <string>
using namespace std;

#include "HR_AutoLock.h"
#include "HR_SingletonBase.h"
class HR_FSM
{
DECLARE_Singleton(HR_FSM)
public:
static SaftLock m_FSMLock;
private:
    
    string m_strExeDir;//
    /* data */
    vector<string> m_strTimerCmd;
public:
   void Initialize(const string& strExeDir);

   void HandleMsg(const string&cmd,const vector<string>&param,vector<string>&result);

   void HandleTimer();
};

#define HRFSMObj HR_FSM::instance()

#endif // _HR_FSM_H