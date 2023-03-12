### Event send
```   
    rtems_status_code rtems_event_send (
          rtems_id        id,
          rtems_event_set event_in
    );
```   

By using rtems_event_send function， the event value indicated by "event_in" will be set to RTEMS API's   
"pending_event" variable.  And then the thread to receive the event will be checked, is the thread is in   
waiting state for the event, the thread will be unblocked and get it ready to be dispatched.


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
will be executed again when event sending thread sending the event signal and putting it on ready list. Then the   
the thread will be scheduled .
