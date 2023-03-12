### Test code 
``` 
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
```    

***   
***
### Event send
```   
    rtems_status_code rtems_event_send (
          rtems_id        id,
          rtems_event_set event_in
    );
```   

By using rtems_event_send function， the event value indicated by "event_in" will be set to RTEMS API's     
"pending_event" variable.  And then the thread to receive the event will be checked, is the thread is in     
waiting state for the event, the thread will be unblocked and get it ready to be dispatched. At this moment    
the receiving thread will not get running immediatelly.  Untill the "rtems_task_wake_after" is called the   
dispatch procedure in which will run. Then the receiving thread will be scheduled.     


*** 
***

### Event receive
```   
rtems_status_code rtems_event_receive (
  rtems_event_set  event_in,
  rtems_option     option_set,
  rtems_interval   ticks,
  rtems_event_set *event_out
);
```    
By using "rtems_event_receive" function, the receiving thread will check whether the pending event is on RTEMS API's    
pending event list. If not, the thread will be blocked by itself and thread dispatch will occure. The receiving thread    
will be executed again when event sending thread sending the event signal and putting it on ready list. Then after the   
sending thread getting sleep, the receiving thread will be scheduled. 
