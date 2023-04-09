### const Scheduler_Control _Scheduler_Table[] =
{
  CONFIGURE_SCHEDULER_TABLE_ENTRIES
};

##### Structure defination
```
/**
 * @brief Scheduler control.
 */
struct _Scheduler_Control {
  /**
   * @brief Reference to a statically allocated scheduler context.
   */
  Scheduler_Context *context;

  /**
   * @brief The scheduler operations.
   */
  Scheduler_Operations Operations;

  /**
   * @brief The maximum priority value of this scheduler.
   *
   * It defines the lowest (least important) thread priority for this
   * scheduler.  For example the idle threads have this priority.
   */
  Priority_Control maximum_priority;

  /**
   * @brief The scheduler name.
   */
  uint32_t name;

#if defined(RTEMS_SMP)
  /**
   * @brief True if the non-preempt mode for threads is supported by the
   * scheduler, otherwise false.
   */
  bool is_non_preempt_mode_supported;
#endif
};
``` 

The above macro CONFIGURE_SCHEDULER_TABLE_ENTRIES  consist of following elements:   
```    
{ \
      &_Configuration_Scheduler_priority_dflt.Base.Base, \
      { \
         _Scheduler_priority_Initialize,       /* initialize entry point */ \
         _Scheduler_priority_Schedule,         /* schedule entry point */ \
         _Scheduler_priority_Yield,            /* yield entry point */ \
         _Scheduler_priority_Block,            /* block entry point */ \
         _Scheduler_priority_Unblock,          /* unblock entry point */ \
         _Scheduler_priority_Update_priority,  /* update priority entry point */ \
         _Scheduler_default_Map_priority,      /* map priority entry point */ \
         _Scheduler_default_Unmap_priority,    /* unmap priority entry point */ \
         \
         _Scheduler_priority_Node_initialize,  /* node initialize entry point */ \
         _Scheduler_default_Node_destroy,      /* node destroy entry point */ \
         _Scheduler_default_Release_job,       /* new period of task */ \
         _Scheduler_default_Cancel_job,        /* cancel period of task */ \
         _Scheduler_default_Start_idle         /* start idle entry point */ \
         \
      }, \
      ( sizeof( _Configuration_Scheduler_priority_dflt.Ready ) / sizeof( ( _Configuration_Scheduler_priority_dflt.Ready )[ 0 ] ) ) - 1, \
      ( ( (uint32_t) (uint8_t) ('U') << 24 | (uint32_t) (uint8_t) ('P') << 16 | (uint32_t) (uint8_t) ('D') << 8 | (uint8_t) (' ') ) ) \
       \
}
```   
