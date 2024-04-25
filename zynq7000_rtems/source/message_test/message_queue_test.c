
#include <rtems.h>
//#include <cpuuse.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct {
	float So;
	float Bo;
	uint8_t orbit_ok;
}My_Message;

#define MESSAGE_SIZE	(sizeof(My_Message))
rtems_id message_queue_id;




//produce message
rtems_task message_queue_fun1(rtems_task_argument ununsed)
{
	rtems_status_code status;
	int i;
	size_t pending_nm;
	My_Message msg_send_buf[2];
	msg_send_buf[0].Bo = 1.0;
	msg_send_buf[0].So = 2.0;
	msg_send_buf[0].orbit_ok = 1;
	msg_send_buf[1].Bo = -1.0;
	msg_send_buf[1].So = -2.0;
	msg_send_buf[1].orbit_ok = 1;

	while(1)
	{
		for(i=0; i<sizeof(msg_send_buf) / MESSAGE_SIZE; i++)
		{
			//Note: message can be only sent to queue one by one. The following is wrong:
			//rtems_message_queue_send( message_queue_id, msg_send_buf, MESSAGE_SIZE * 2)
			status = rtems_message_queue_send( message_queue_id, &msg_send_buf[i], MESSAGE_SIZE );

			if(RTEMS_SUCCESSFUL != status)
			{
				printf("message send failed\n");
				exit(1);
			}
			status = rtems_message_queue_get_number_pending(message_queue_id, &pending_nm);
			printf("Pending nm: %d\n", pending_nm);
		}

		//change the message value
		msg_send_buf[0].Bo += 1.0;
		msg_send_buf[0].So += 0.1;
		msg_send_buf[0].orbit_ok += 1;
		msg_send_buf[1].Bo -= 1.0;
		msg_send_buf[1].So -= 0.1;
		msg_send_buf[1].orbit_ok += 1;

		printf("\n****** In message queue fun1 ******\n\n");
		rtems_task_wake_after(1500);

	}

}


//receive message
rtems_task message_queue_fun2(rtems_task_argument ununsed)
{
	rtems_status_code status;
	My_Message msg_buf[2];
	size_t size;
	int i;

	while(1)
	{
		status = rtems_message_queue_receive(
				message_queue_id,
				msg_buf,
				&size,
				RTEMS_DEFAULT_OPTIONS,
				0
		);
		if(RTEMS_SUCCESSFUL != status)
		{
			exit(0);
		}

		printf("###### In message queue fun2 ######\n");
		printf("Received %d message\n", size/MESSAGE_SIZE);
		printf("Message is : \n");
		for(i=0; i<size/MESSAGE_SIZE; i++)
		{
			printf("%f\t %f\t %d\n", msg_buf[i].Bo, msg_buf[i].So, msg_buf[i].orbit_ok );
		}

	}
}


rtems_task message_queue_test_fun(rtems_task_argument unused)
{
	rtems_status_code status;
	rtems_id queue_test_id1, queue_test_id2;

	//create message queue
	/* count == 0 */
	status = rtems_message_queue_create(
			rtems_build_name('M', 'S', 'G', '1'),
			4,
			MESSAGE_SIZE,
			RTEMS_DEFAULT_ATTRIBUTES,
			&message_queue_id
	);

	//create 2 threads
	status = rtems_task_create(
			rtems_build_name('M', 'S', 'T', '1'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&queue_test_id1
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	status = rtems_task_create(
			rtems_build_name('M', 'S', 'T', '2'),
			1,
			RTEMS_MINIMUM_STACK_SIZE * 2,
			RTEMS_DEFAULT_MODES,
			RTEMS_DEFAULT_ATTRIBUTES,
			&queue_test_id2
	);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	//##############################################3
	// start threads
	status = rtems_task_start(queue_test_id1, message_queue_fun1, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}

	status = rtems_task_start(queue_test_id2, message_queue_fun2, 1);
	if(RTEMS_SUCCESSFUL != status)
	{
		exit(0);
	}


	rtems_task_exit();




}
