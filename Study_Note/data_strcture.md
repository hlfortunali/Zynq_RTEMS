### _RTEMS_tasks_Objects 
    Store all task TCB.   
    
### _RTEMS_tasks_Information
**Manage information about task, as thread queue, objects chain.  It manages following data strcture.**

**concerning data structure：**   

```
static Objects_Control * _RTEMS_tasks_Local_table[ 8 ]; \   //8 is according to the set of max_thread configureation defined by CONFIGURE_MAXIMUM_TASKS
static Thread_Configured_control _RTEMS_tasks_Objects[ 8 ]; \
static Thread_queue_Configured_heads _RTEMS_tasks_Heads[ 8 ]; \
Thread_Information _RTEMS_tasks_Information = {  
{ 
    _Objects_Build_id( api, cls, 1, 8 ), 
    _RTEMS_tasks_Local_table, 
    _Objects_Is_unlimited( 8) ? _Thread_Allocate_unlimited : _Objects_Allocate_static,
    _Objects_Is_unlimited( 8) ? _Objects_Free_unlimited : _Objects_Free_static,
    0, 
    _Objects_Is_unlimited(8) ? _Objects_Maximum_per_allocation( 8) : 0, 
    sizeof( Thread_Configured_control ), 
    OBJECTS_NO_STRING_NAME, 
    { { { &_RTEMS_tasks_Information.Objects.Inactive.Tail.Node, NULL }, &_RTEMS_tasks_Information.Objects.Inactive.Head.Node } },
    NULL, 
    NULL, 
    &_RTEMS_tasks_Objects[ 0 ].Control.Object 
  }, 
{ 
    &_RTEMS_tasks_Heads[ 0 ] 
  } 
}
```     
_RTEMS_tasks_Information.Objects.Inactive.Head.Node.Next point to _RTEMS_tasks_Objects[ 0 ]; Tail.Node.Previous point to   
_RTEMS_tasks_Objects[ 0 ]。 This will form a bidirection chain。
When a new task is created the system will allocate a Thread_Control object from the Inactive table.
    
### _Per_CPU_Information
    Store the CPU inforamtion for each CPU.
