#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Timer.h"

int IsPrimeNumber(int _n)
{
	if(_n < 2)
	{
		return 0;
	}
	else
	{
		int retVal = 1;

		for(int i = 2; i < _n; ++i)
		{
			if((_n % i) == 0)
			{
				retVal = 0;
				break;
			}
		}

		return retVal;
	}
}

int GetNumberOfPrimeNumber(int _s, int _e, int _offset)
{
	int retVal = 0;

	for(int i = _s; i <= _e; i += _offset)
	{
		if(IsPrimeNumber(i))
		{
			++retVal;
		}
	}

	return retVal;
}

int main(int _pn, char** _ps)
{
	if((_pn > 4) || (_pn < 4))
	{
		printf("<parameter format> range_start range_end number_process \n");

		exit(1);
	}

	int range_start = atoi(_ps[1]);
	int range_end = atoi(_ps[2]);
	int number_process = atoi(_ps[3]);

	printf("[ parameter list ] \n");
	printf("- range : (%d ~ %d) \n", range_start, range_end);
	printf("- number of process : %d \n", number_process);
	printf("\n");

	pid_t myPID = -1;
	TimerInit(number_process);
	for(int i = 0; i < number_process; ++i)
	{
		myPID = fork();	

		if(myPID == 0)
		{
			TimerStart(i);
			printf("PID %d has found %d prime number(s) \n", (int)getpid(), GetNumberOfPrimeNumber(range_start + i, range_end, number_process));
			TimerEnd(i);
			TimerPrint(i);
			return 0;
		}
		else
		{
			continue;
		}
	}

	for(int i = 0; i < number_process; ++i)
	{
		int status = -1;
		wait(&status);
	}
	TimerQuit();

	return 0;
}
