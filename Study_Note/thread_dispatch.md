#### thread dispatch
   Scenario： Creating 3 tasks and put tasks to sleep by using "rtems_task_wake_after" function. 
     
   The interrupt handler of "_ARMV4_Exception_interrupt" will execute every 1ms.  
     As every thread has a watchdog registed on cpu's whatdog list. So, in the "_Watchdog_Tick"    
     function every thread's  watchdog will be checked. If one or more thread's whatdog expired   
     the the thread timeout event occured. Then the thread will be unlocked by calling "_Thread_Unblock",   
     "_Scheduler_Unblock" and sequencially "_Scheduler_Update_heir" function.  In "_Scheduler_Update_heir "   
     the  " _Thread_Dispatch_necessary = true'" will set the dispatch_necessery as true. Because the   
     macro of "_Thread_Dispatch_necessary" is defined as "_Per_CPU_Get()->dispatch_necessary" .  Also, in
      "_Scheduler_Update_heir "  function the hire thread will be updated, the newly thread that to be 
      exectuted will become the hire. 
      
   So, the procedure is that the interrupt check the time event for each task and set dispatch flag and   
   change the hire thread.  Then the dispatch function change the thread contex.
     
   Then after processing the interrupt, the "_ARMV4_Exception_interrupt" will check whehter    
   thread dispatch is needed. The code is as following:      
```      
          /* Load some per-CPU variables */
            ldr	r0, [SELF_CPU_CONTROL, #PER_CPU_THREAD_DISPATCH_DISABLE_LEVEL] 
            ldrb	r1, [SELF_CPU_CONTROL, #PER_CPU_DISPATCH_NEEDED]  
            ldr	r2, [SELF_CPU_CONTROL, #PER_CPU_ISR_DISPATCH_DISABLE]
            ldr	r3, [SELF_CPU_CONTROL, #PER_CPU_ISR_NEST_LEVEL]

            /* Restore stack pointer */
            mov	sp, NON_VOLATILE_SCRATCH

            /* Save CPSR in non-volatile register */
            mrs	NON_VOLATILE_SCRATCH, CPSR

            /* Decrement levels and determine thread dispatch state */
            eor	r1, r0
            sub	r0, #1
            orr	r1, r0
            orr	r1, r2
            sub	r3, #1

            /* Store thread dispatch disable and ISR nest levels */
            str	r0, [SELF_CPU_CONTROL, #PER_CPU_THREAD_DISPATCH_DISABLE_LEVEL]
            str	r3, [SELF_CPU_CONTROL, #PER_CPU_ISR_NEST_LEVEL]

            /*
             * Check thread dispatch necessary, ISR dispatch disable and thread
             * dispatch disable level.
             */
            cmp	r1, #0
            bne	.Lthread_dispatch_done

            /* Thread dispatch */
            mrs	NON_VOLATILE_SCRATCH, CPSR    
            
            .Ldo_thread_dispatch:   //the thread dispatch section 
```       
  The "SELF_CPU_CONTROL" macro is defined as r7, and r7 stores the address of "_Per_CPU_Information"   
  structure. 
     
  The code of "   ldrb	r1, [SELF_CPU_CONTROL, #PER_CPU_DISPATCH_NEEDED]   " in above section will load the   
  parameter of "dispatch_necessery" in structure "_Per_CPU_Information" into r1. 
    
  Then the following 3 lines of code will judge whehter dispatch is needed.    
``` 
            cmp	r1, #0
            bne	.Lthread_dispatch_done

            /* Thread dispatch */
            mrs	NON_VOLATILE_SCRATCH, CPSR    
            
           .Ldo_thread_dispatch:   //the thread dispatch section  
```     
  
  If r1 is equal to 0, this means dispatch_necessery flag is not set.  The code will run to    
  ".Lthread_dispatch_done". Thread dispatch procedure is skipt. Ohterwise, if r1 is queal to 1   
  this means the dispatch_necessery flag is set. The code will run to ".Ldo_thread_dispatch:".   
  Then thread dispatch function will be executed.   
  
    
