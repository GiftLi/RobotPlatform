#include "BaseShareMemory.h"

ShareMemory::ShareMemory()
{
	/* 创建线程 */
	if(-1 == pthread_create(&m_syncThread, nullptr, syncThread, this))
	{
		printf("create pthread error on ShareMemory\n");

		return -1;
	}
}

	
ShareMemory::~ShareMemory();
{

}

void* ShareMemory::syncThread(void* pParam)
{
	__useconds_t MS_20 = 20 * 1000;
	
	while(true)
	{
		syncHandle();
		
		usleep(MS_20);
	}
}

bool ShareMemory::syncHandle(void)
{
	/*  注意这个刷新读数据区不能刷新codesys给代理的请求命令，
	  @ 应该由上层应用者自行开一条线程刷新，不然会冲刷掉一些命令，
	  @ 例如上一个请求还没有处理时，已经 被冲刷到下一次。 
	*/

	/* 连接状态更新 */
	//获取数据：读区域
	
	//获取数据：写返回

	//喂狗
}





