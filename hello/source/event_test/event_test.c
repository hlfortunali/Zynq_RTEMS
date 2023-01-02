
#include <rtems.h>
//#include <cpuuse.h>
#include <stdlib.h>
#include <stdio.h>



rtems_id event_test_id1, event_test_id2;


//send event
rtems_task event_fun1(rtems_task_argument ununsed)
{
	rtems_status_code status;

	while(1)
	{

		status = rtems_event_send( event_test_id2, RTEMS_EVENT_16 );
		if(RTEMS_SUCCESSFUL != status)
		{
			printf("event send failed\n");
			exit(1);
		}

		printf("\n****** In event fun1 ******\n\n");
		rtems_task_wake_after(2500);
	}

}


//receive message
rtems_task event_fun2(rtems_task_argument ununsed)
{
	rtems_status_code status;
	rtems_event_set   event_out;

	while(1)
	{
		status = rtems_event_receive(
				RTEMS_EVENT_16,
				RTEMS_WAIT,
				RTEMS_NO_TIMEOUT,
				&event_out
		);
		if(RTEMS_SUCCESSFUL != status)
		{
			exit(0);
		}

		printf("###### In event fun2, Event received! ######\n");

	}
}


rtems_task event_test_fun(rtems_task_argument unused)
{
	rtems_status_code status;



	//create 2 threads
	status = rtems_task_create(
			rtems_build_name('E', 'V', 'T', '1'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&event_test_id1
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	status = rtems_task_create(
			rtems_build_name('E', 'V', 'T', '2'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&event_test_id2
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	//##############################################3
	// start threads
	status = rtems_task_start(event_test_id1, event_fun1, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(event_test_id2, event_fun2, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	rtems_task_exit();




}
