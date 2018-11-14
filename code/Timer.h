#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

struct Timer
{
	struct timeval mSrc;
	struct timeval mDst;
};

static struct Timer* gTimers = NULL;
static int gTimerNum = -1;

int TimerInit(int _tn)
{
	if(_tn > 0)
	{
		gTimerNum = _tn;
		gTimers = (struct Timer*)malloc(sizeof(struct Timer) * gTimerNum);
		return 0;
	}
	else
	{
		printf("TimerInit() : you cannot make less than 1 timer(s) \n");
		return -1;
	}
}

int TimerQuit()
{
	if(gTimers)
	{
		gTimerNum = -1;
		free(gTimers);
		gTimers = NULL;
		return 0;
	}
	else
	{
		printf("TimerQuit() : you cannot call this function before TimerInit() \n");
		return -1;
	}
}

int TimerStart(int _tid)
{
	if(gTimers == NULL)
	{
		printf("TimerStart() : you cannot call this function before TimerInit() \n");
		return -1;
	}

	if(_tid < gTimerNum)
	{
		gettimeofday(&(gTimers[_tid].mSrc), NULL);
		return 0;
	}
	else
	{
		printf("TimerStart() : you cannot index more than (number of timers - 1) \n");
		return -1;
	}
}

int TimerEnd(int _tid)
{
	if(gTimers == NULL)
	{
		printf("TimerEnd() : you cannot call this function before TimerInit() \n");
		return -1;
	}

	if(_tid < gTimerNum)
	{
		gettimeofday(&(gTimers[_tid].mDst), NULL);
		return 0;
	}
	else
	{
		printf("TimerEnd() : you cannot index more than (number of timers - 1) \n");
		return -1;
	}
}

int TimerPrint(int _tid)
{
	if(gTimers == NULL)
	{
		printf("TimerPrint() : you cannot call this function before TimerInit() \n");
		return -1;
	}

	if(_tid < gTimerNum)
	{
		printf("elapsed time : %d milli-second(s) \n", (int)(gTimers[_tid].mDst.tv_sec - gTimers[_tid].mSrc.tv_sec) * 1000 + (int)(gTimers[_tid].mDst.tv_usec - gTimers[_tid].mSrc.tv_usec) / 1000);
		return 0;
	}
	else
	{
		printf("TimerPrint() : you cannot index more than (number of timers - 1) \n");
		return -1;
	}
}
