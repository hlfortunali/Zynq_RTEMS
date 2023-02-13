#### User defined programme is started from the Init task. This note record the user defined Init task procedure.   
    
   We can see from the code, CONFIGURE_INIT_TASK_ENTRY_POINT macro point to the user task initialization point function.   
   And the "Init" task parameters are defined by several macro in "_RTEMS_tasks_User_task_table" variable.   
   Then the "_RTEMS_tasks_Initialize_user_task" is placed in SYSINIT list.    
   Then the "Init" task is created in "_RTEMS_tasks_Initialize_user_task" function, and this function is called in initialization   
   procedure of "rtems_initialize_executive".
    
    
    code :
    #ifndef CONFIGURE_INIT_TASK_ENTRY_POINT
        rtems_task Init( rtems_task_argument );
        #define CONFIGURE_INIT_TASK_ENTRY_POINT Init

        #ifndef CONFIGURE_INIT_TASK_ARGUMENTS
            extern const char *bsp_boot_cmdline;
        #define CONFIGURE_INIT_TASK_ARGUMENTS ( (rtems_task_argument) &bsp_boot_cmdline )
        #endif
    #endif

    #ifndef CONFIGURE_INIT_TASK_ARGUMENTS
    #define CONFIGURE_INIT_TASK_ARGUMENTS 0
    #endif

    const rtems_initialization_tasks_table _RTEMS_tasks_User_task_table = {
      CONFIGURE_INIT_TASK_NAME,
      CONFIGURE_INIT_TASK_STACK_SIZE,
      CONFIGURE_INIT_TASK_PRIORITY,
      CONFIGURE_INIT_TASK_ATTRIBUTES,
      CONFIGURE_INIT_TASK_ENTRY_POINT,
      CONFIGURE_INIT_TASK_INITIAL_MODES,
      CONFIGURE_INIT_TASK_ARGUMENTS
    };

    RTEMS_SYSINIT_ITEM(
      _RTEMS_tasks_Initialize_user_task,
      RTEMS_SYSINIT_CLASSIC_USER_TASKS,
      RTEMS_SYSINIT_ORDER_MIDDLE
    );
