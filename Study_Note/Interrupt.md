
***
***
***
# Interrupt 
### Interrupt initialization : 

    in start.s the exception vector table is set
    
    bsp_start_vector_table_begin:

	ldr	pc, .Lhandler_addr_reset
	ldr	pc, .Lhandler_addr_undef
	ldr	pc, .Lhandler_addr_swi
	ldr	pc, .Lhandler_addr_prefetch
	ldr	pc, .Lhandler_addr_abort

	/* Program signature checked by boot loader */
	.word	0xb8a06f58

	ldr	pc, .Lhandler_addr_irq
	ldr	pc, .Lhandler_addr_fiq
    
    .Lhandler_addr_reset:

    #ifdef BSP_START_RESET_VECTOR
	    .word	BSP_START_RESET_VECTOR
    #else
	    .word	_start
    #endif

    .Lhandler_addr_irq：	.word	_ARMV4_Exception_interrupt
    
    
   #### Please note that the irq handler( Lhandler_addr_irq) is set to "_ARMV4_Exception_interrupt".   
   #### When irq occured the command " ldr pc, .Lhadler_addr_irq" will be executed. That is to say " _ARMV4_Exception_interrupt" function will be executed.
  
    If a vector is installed by using "rtems_interrupt_handler_install" function in initialization procedure,   
    then this vector can be dispatched from the registered list by calling "bsp_interrupt_dispatch" function in " _ARMV4_Exception_interrupt".
  #### The above mentioned method is commonly used in RTOS. So that the RTOS's interrupt handler can control and pass parameters to user defined interrupt handler.
  
    All irq use the same handler. Thid mode is called un-vector interrupt mode. Cortex A9 use this mode.
    
    And after that the thread dispatcher will be executed if needed.
    Then return to interrupted point.

  #### The following part in initialization procedure setting cp15 interrupt handler to " _ARMV4_Exception_interrupt" too. This need to be further studied. 
    bsp_start --> bsp_interrupt_initialize -->
    rtems_status_code bsp_interrupt_facility_initialize(void)
    {
     volatile gic_cpuif *cpuif = GIC_CPUIF;
     volatile gic_dist *dist = ARM_GIC_DIST;
     uint32_t id_count = get_id_count(dist);
    uint32_t id;

    arm_cp15_set_exception_handler(
    ARM_EXCEPTION_IRQ,
    _ARMV4_Exception_interrupt
    ); 
    .......   to be continue 