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
