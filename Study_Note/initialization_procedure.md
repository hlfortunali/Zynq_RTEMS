####  _Workspace_Handler_initialization funcion
    This function is used to initialization the heap for RTEMS.   
    The space (Memery_area) is defined in linkdcmd.base file.    
    After this procedure a pointer will point to the heap area.


#### RTEMS_Malloc_Initialize function
    
    
    
#### bsp_start function



#### zynq_debug_console_init

#### _Thread_Handler_initialization --> _Thread_Initialize_information

        /**
         * @brief The thread object information.
         */
        typedef struct {
          /**
           * @brief The object information.
           */
          Objects_Information Objects;

          /**
           * @brief Thread queue heads maintenance.
           */
          union {
            /**
             * @brief Contains the initial set of thread queue heads.
             *
             * This is set by <rtems/confdefs.h> via THREAD_INFORMATION_DEFINE().
             */
            Thread_queue_Configured_heads *initial;

            /**
             * @brief The free thread queue heads.
             *
             * This member is initialized by _Thread_Initialize_information().
             */
            Freechain_Control Free;
          } Thread_queue_heads;
        } Thread_Information;
        
        
      THREAD_INFORMATION_DEFINE(
      _Thread,
      OBJECTS_INTERNAL_API,
      OBJECTS_INTERNAL_THREADS,
      _CONFIGURE_MAXIMUM_PROCESSORS + _CONFIGURE_MPCI_RECEIVE_SERVER_COUNT
      );
      
    Above macro will be explained as following:   

    static Objects_Control * _Thread_Local_table[ _Objects_Maximum_per_allocation( max ) ]; 
    static Thread_Configured_control _Thread_Objects[ _Objects_Maximum_per_allocation( max ) ]; 
    static Thread_queue_Configured_heads _Thread_Heads[ _Objects_Maximum_per_allocation( max ) ]; 
    Thread_Information _Thread_Information = { 
      { 
        _Objects_Build_id( api, cls, 1, _Objects_Maximum_per_allocation( max ) ), 
        _Thread_Local_table, 
        _Objects_Is_unlimited( max ) ? _Thread_Allocate_unlimited : _Objects_Allocate_static, 
        _Objects_Is_unlimited( max ) ? _Objects_Free_unlimited : _Objects_Free_static, 
        0, 
        _Objects_Is_unlimited( max ) ? _Objects_Maximum_per_allocation( max ) : 0, 
        sizeof( Thread_Configured_control ), 
        OBJECTS_NO_STRING_NAME, 
        CHAIN_INITIALIZER_EMPTY( _Thread_Information.Objects.Inactive ), 
        NULL, 
        NULL, 
        &_Thread_Objects[ 0 ].Control.Object 
        OBJECTS_INFORMATION_MP( _Thread_Information.Objects, NULL ) 
      }, 
      { 
        &_Thread_Heads[ 0 ] 
      } 
    }
    
 Note : After initialization the element of "Chain_Control Inactive" will connect to the _Thread_Objects[ 0 ].Control.Object.   
        The elemetn of "Thread_queue_Configured_heads *initial " will point to _Thread_Heads[0].
           
     _Freechain_Initialize(
    &information->Thread_queue_heads.Free,
    information->Thread_queue_heads.initial,
    _Objects_Get_maximum_index( &information->Objects ),
    _Thread_queue_Heads_size
    );
    This function finally initializ the chain to connect _Thread_Heads.  That is head.Next point to _Thread_Heads[0] and    
    Thared_Heads[0].next point to tail.   
    
    
#### _Scheduler_Handler_initialization
    Initializating the priority map and chain.
    
#### _RTEMS_tasks_Manager_initialization
    1.  _Thread_Initialize_information( &_RTEMS_tasks_Information );  
         This function initializes the _RTEMS_tasks_Information array and connect the inacitve chain control node to _RTEMS_task_
    _User_extensions_Add_API_set( &_RTEMS_tasks_User_extensions );
