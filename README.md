# zynq_RTEMS
RTEMS demo for zynq 7010


## Debug use Xilinx Vitis
1. build the RTEMS app following the official guide, then you will get hello.exe(for example)
2. Create a Vitis project, we call it hello project. I use 2022.2 version.
3. Test the vitis project and debug it, if it can successfully output "hello world" in serial console, this means the project and debug configure are both ok.
4. Set the debug configure for hello project in Vitis. Just change the Application section. Here, we select the RTEMS app hello.exe. 
5. Start debugging and open the XSCT Console windows.
6. Then you can debug the RTEMS app by using XSCT command.  The XSCT command can be checked on Xilinx's website.


## to be continue ...
