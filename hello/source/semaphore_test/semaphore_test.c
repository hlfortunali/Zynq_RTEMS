
#include <rtems.h>
//#include <cpuuse.h>
#include <stdlib.h>
#include <stdio.h>

rtems_id semaphore_id;



rtems_task semaphore_fun1(rtems_task_argument ununsed)
{
	rtems_status_code status;

	while(1)
	{
		status = rtems_semaphore_obtain(
						semaphore_id,
						RTEMS_DEFAULT_OPTIONS,
						RTEMS_NO_TIMEOUT
				);

		printf("In semaphore fun1\n");
		rtems_task_wake_after(1500);

		status = rtems_semaphore_release( semaphore_id);

		rtems_cpu_usage_report();
	}

}



rtems_task semaphore_fun2(rtems_task_argument ununsed)
{
	rtems_status_code status;

	while(1)
	{
		status = rtems_semaphore_obtain(
				semaphore_id,
				RTEMS_DEFAULT_OPTIONS,
				RTEMS_NO_TIMEOUT
		);
		if(RTEMS_SUCCESSFUL != status)
		{
			exit(0);
		}

		printf("In semaphore fun2\n");
		status = rtems_semaphore_release( semaphore_id);

	}
}


rtems_task semaphore_test_fun(rtems_task_argument unused)
{
	rtems_status_code status;
	rtems_id sm_test_id1, sm_test_id2;

	//create semaphore
	status = rtems_semaphore_create(
			rtems_build_name('S', 'M', '0', '1'),
			1,
			RTEMS_PRIORITY,
			RTEMS_NO_PRIORITY,
			&semaphore_id
	);

	//create 2 threads
	status = rtems_task_create(
			rtems_build_name('S', 'M', 'T', '1'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&sm_test_id1
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	status = rtems_task_create(
			rtems_build_name('S', 'M', 'T', '2'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&sm_test_id2
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	//##############################################3
	// start threads
	status = rtems_task_start(sm_test_id1, semaphore_fun1, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(sm_test_id2, semaphore_fun2, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	rtems_task_exit();




}
