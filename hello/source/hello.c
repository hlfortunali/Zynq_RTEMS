/*
 * Hello world example
 */
#include "task1.h"
#include "task2.h"
#include "get_date.h"
#include "semaphore_test.h"
#include "message_queue_test.h"
#include "event_test.h"

#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>



rtems_task Init(
		rtems_task_argument ignored
)
{

	rtems_status_code status;
	rtems_name Task_name;
	rtems_id task_id1, task_id2, task_id3, task_id_test_fun;

	//######################################################
	Task_name = rtems_build_name('T', 'A', '0', '1');
	status = rtems_task_create(
			Task_name,
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id1
	);

	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	Task_name = rtems_build_name('T', 'A', '0', '2');
	status = rtems_task_create(
			Task_name,
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id2
	);

	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_create(
			rtems_build_name('T', 'A', '0', '3'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id3
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	status = rtems_task_create(
			rtems_build_name('T', 'E', 'S', 'T'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id_test_fun
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	//################################################################
//	status = rtems_task_start(task_id1, thread1_fun, 1);
//	if(RTEMS_SUCCESSFUL != status)
//	{
//		exit(0);
//	}

//	status = rtems_task_start(task_id2, thread2_fun, 1);
//	if(RTEMS_SUCCESSFUL != status)
//	{
//		exit(0);
//	}

//	status = rtems_task_start(task_id3, get_date_fun, 1);
//	if(RTEMS_SUCCESSFUL != status)
//	{
//		exit(0);
//	}


	status = rtems_task_start(task_id_test_fun, event_test_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	rtems_task_exit();
}
