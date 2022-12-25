# Zynq_RTEMS
RTEMS demo for zynq 7010


## Debug use Xilinx Vitis
1. build the RTEMS app following the official guide, then you will get hello.exe(for example)
2. Create a Vitis project, we call it hello project. I use Vitis 2022.2 version. 
3. Test the vitis project and debug it, if it can successfully output "hello world" in serial console, this means the project and debug configure are both ok.
4. Set the debug configure for hello project in Vitis. Just change the Application section. Here, we select the RTEMS app hello.exe. 
5. Start debugging and open the XSCT Console windows. (reference to : https://china.xilinx.com/htmldocs/xilinx2017_1/SDK_Doc/index.html?q=/htmldocs/xilinx2017_1/SDK_Doc/xsct/use_cases/xsdb_standalone_app_debug.html)
6. Then you can debug the RTEMS app by using XSCT command.  The XSCT command can be checked on Xilinx's website.

## Problem
1.   Cannot read symbol data. Invalid abbreviation table. Error reading DWARF data   
When debuging following the above steps, this error may appear.  This reason is that RTEMS gcc version and the Xilinx Vistis GDB version are not compatiable. The solution is upgrade your Vitis version or downgrade your RTEMS version.   RTEMS6 and Vitis2022.2 can work. RTEMS5 and Vitis2020.1 can also work. Other versions are not tested.
## to be continue ...
