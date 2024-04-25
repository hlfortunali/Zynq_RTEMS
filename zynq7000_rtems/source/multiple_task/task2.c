#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

rtems_task thread2_fun(rtems_task_argument unused)
{
	static int thread2_cnt = 0;
	while(1)
	{
		thread2_cnt++;
		printf("Hello RTEMS thread2 ************ %8d\n", thread2_cnt);
		rtems_task_wake_after(2000);
	}
}
