### _RTEMS_tasks_Objects 
    Store all task TCB.   
    
### _RTEMS_tasks_Information
Manage information about task, as thread queue, objects chain.  It manages following data strcture.
``` 
static Objects_Control * _RTEMS_tasks_Local_table[ MAX_THREAD_NM ];  
static Thread_Configured_control _RTEMS_tasks_Objects[ MAX_THREAD_NM ];
static Thread_queue_Configured_heads _RTEMS_tasks_Heads[ MAX_THREAD_NM ];
```   
    
### _Per_CPU_Information
    Store the CPU inforamtion for each CPU.
