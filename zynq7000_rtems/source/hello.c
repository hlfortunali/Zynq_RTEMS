/*
 * Hello world example
 */
#include <multiple_task/task1.h>
#include <multiple_task/task2.h>
#include "semaphore_test.h"
#include "message_queue_test.h"
#include "event_test.h"

#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <time_test/get_date.h>

//#define TEST_MULTIPLE_TASK
//#define TEST_EVENT
#define TEST_SEMAPHORE
//#define TEST_MESSAGE_QUEUE

rtems_task Init(
		rtems_task_argument ignored
)
{

	rtems_status_code status;
	rtems_name Task_name;


#ifdef TEST_MULTIPLE_TASK
	//######################################################
	rtems_id task_id1, task_id2, task_id3;
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





	//################################################################
	status = rtems_task_start(task_id1, thread1_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(task_id2, thread2_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(task_id3, get_date_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}
#endif //end of TEST_MULTIPLE_TASK


#ifdef TEST_EVENT
	rtems_id task_id_test_fun;
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

	status = rtems_task_start(task_id_test_fun, event_test_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}
#endif


#ifdef TEST_SEMAPHORE
	rtems_id task_id_test_semaphore;
	status = rtems_task_create(
			rtems_build_name('T', 'S', 'T', '1'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id_test_semaphore
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(task_id_test_semaphore, semaphore_test_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}
#endif


#ifdef TEST_MESSAGE_QUEUE
	rtems_id task_id_test_msg_queue;
	status = rtems_task_create(
			rtems_build_name('T', 'S', 'T', '2'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&task_id_test_msg_queue
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(task_id_test_msg_queue, message_queue_test_fun, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}
#endif


	rtems_task_exit();
}
