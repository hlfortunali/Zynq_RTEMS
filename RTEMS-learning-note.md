### rtems_initialize_executive  automatic initializing: 
在文件'src/rtems/bsps/shared/start/bootcard.c'中
boot_card ---> rtems_initialize_executive

在文件'src/rtems/cpukit/sapi/src/exint.c'中
rtems_initialize_executive ---> RTEMS_LINKER_SET_FOREACH(_Sysinit, item) { (*item->handler)(); }

在文件'src/rtems/cpukit/include/rtems/linkersets.h'中
#define RTEMS_LINKER_SET_FOREACH(set, item)                                     \
for (                                                                           \
    item = (void *)_Linker_set_Obfuscate(RTEMS_LINKER_SET_BEGIN(set)) ;         \
    item != RTEMS_LINKER_SET_END(set) ;                                         \
    ++item                                                                      \
)

在文件'src/rtems/bsps/shared/start/linkcmds.base'中通过 SORT 可以将 content 放置于 begin 与 end 之间 (关于content的排序受order字段和名称字符串排序)

.rtemsroset : ALIGN_WITH_INPUT {
    /* Special FreeBSD linker set sections */
    __start_set_sysctl_set = .;
    *(set_sysctl_*);
    __stop_set_sysctl_set = .;
    *(set_domain_*);
    *(set_pseudo_*);

    KEEP (*(SORT(.rtemsroset.*)))

    /* If requested, align the size of the rodata section to the next power of two to meet MPU region alignment requirements. */
    . = DEFINED (bsp_align_text_and_rodata_end_to_power_of_2) ? bsp_section_rodata_begin + ALIGN (. - bsp_section_rodata_begin, 1 << LOG2CEIL (. - bsp_section_rodata_begin)) : .;

    bsp_section_rodata_end = .;
} > REGION_RODATA AT > REGION_RODATA_LOAD


这样 RTEMS_LINKER_SET_FOREACH 就能完成所有的通过 RTEMS_SYSINIT_ITEM 指定的系统初始化接口了

关于系统初始化框架参考官方文档:
https://docs.freebsd.org/en/books/arch-handbook/sysinit/

***   

### Rate Monotonic Scheduling Algorithm   
RMS is an optimal fixed-priority algorithm for scheduling independent, preemptible, periodic tasks on a single processor.


*** 
### Barrier Manager
A barrier can be viewed as a gate at which tasks wait until the gate is opened. This has many analogies in the real world. Horses and other farm animals may approach a closed gate and gather in front of it, waiting for someone to open the gate so they may proceed. Similarly, ticket holders gather at the gates of arenas before concerts or sporting events waiting for the arena personnel to open the gates so they may enter.

Barriers are useful during application initialization. Each application task can perform its local initialization before waiting for the application as a whole to be initialized. Once all tasks have completed their independent initializations, the “application ready” barrier can be released.






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

  #### The following part in initialia set cp15 interrupt handler to " _ARMV4_Exception_interrupt" too. This need to be further studied. 
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
    
