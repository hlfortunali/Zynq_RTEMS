#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

rtems_task thread1_fun(rtems_task_argument unused)
{
	static int thread1_cnt = 0;
	while(1)
	{
		thread1_cnt++;
		printf("Hello RTEMS thread1 --- %8d\n", thread1_cnt);
		rtems_task_wake_after(1000);
	}
}
