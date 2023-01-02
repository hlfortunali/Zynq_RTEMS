/*
 * Simple RTEMS configuration
 */

#define CONFIGURE_MICROSECONDS_PER_TICK 1000		//set clock tick to 1000us, the default value is 10000
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_UNLIMITED_OBJECTS
#define CONFIGURE_UNIFIED_WORK_AREAS

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>


//###############################################
//########### config for shell ##################
//#define CONFIGURE_SHELL_COMMANDS_INIT
//#define CONFIGURE_SHELL_COMMANDS_ALL
//#define CONFIGURE_SHELL_MOUNT_MSDOS
//#define CONFIGURE_SHELL_MOUNT_NFS
//#include <rtems/shellconfig.h>
//###############################################
