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
	//获取数据：读区域
	
	//获取数据：写返回

	//喂狗
}





