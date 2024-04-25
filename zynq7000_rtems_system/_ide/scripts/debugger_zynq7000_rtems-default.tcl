# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/lee/Documents/VitisSpace2022/zynq7000_rtems_system/_ide/scripts/debugger_zynq7000_rtems-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/lee/Documents/VitisSpace2022/zynq7000_rtems_system/_ide/scripts/debugger_zynq7000_rtems-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/lee/Documents/VitisSpace2022/design_1_wrapper_z7000/export/design_1_wrapper_z7000/hw/design_1_wrapper_z7000.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
targets -set -nocase -filter {name =~ "*A9*#0"}
rst -processor
dow /home/lee/Documents/VitisSpace2022/design_1_wrapper_z7000/export/design_1_wrapper_z7000/sw/design_1_wrapper_z7000/boot/fsbl.elf
set bp_31_50_fsbl_bp [bpadd -addr &FsblHandoffJtagExit]
con -block -timeout 60
bpremove $bp_31_50_fsbl_bp
targets -set -nocase -filter {name =~ "*A9*#0"}
dow /home/lee/Documents/VitisSpace2022/zynq7000_rtems/Debug/zynq7000_rtems.elf
configparams force-mem-access 0
bpadd -addr &main
