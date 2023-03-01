####  _Workspace_Handler_initialization funcion
    This function is used to initialization the heap for RTEMS. The space (Memery_area) is defined in linkdcmd.base file.    
    After this procedure a pointer will point to the heap area.


#### RTEMS_Malloc_Initialize function
    
    
    
#### bsp_start function



#### zynq_debug_console_init

#### _Thread_Handler_initialization --> _Thread_Initialize_information

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
