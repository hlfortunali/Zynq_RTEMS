#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

void print_current_time (rtems_time_of_day *time)

{
	fprintf(stdout,
			"\n\n%d-%d-%d--%d:%d:%d --- %6d\n", time->year, time->month, time->day, time->hour,
			time->minute, time->second, time->ticks);
}

rtems_task get_date_fun(rtems_task_argument unused)
{
	rtems_status_code status;
	rtems_time_of_day time, get_time;
	uint64_t nano_second;


	time.year 	= 2022;
	time.month 	= 12;
	time.day	= 28;
	time.hour	= 20;
	time.minute	= 23;
	time.second	= 0;
	time.ticks	= 0;

	status = rtems_clock_set(&time);

	rtems_id tid;
	status = rtems_task_ident(RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid);
	printf("Task id : %d\n", tid);

	while(1)
	{
		status = rtems_clock_get_tod(&get_time);
		print_current_time(&get_time);
		nano_second = rtems_clock_get_uptime_nanoseconds();
		printf("Nano second: %lld\n\n",nano_second);
		status = rtems_task_wake_after(3000);
	}
}
