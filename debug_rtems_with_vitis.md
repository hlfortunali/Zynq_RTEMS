### Tools 
    1. Ubuntu18.04.2
    2. Vitis2020.1
    3. RTEMS5.1
    4. Zynq board (AX7010 from Alinx company)
    
    
### Debug use Xilinx Vitis
    1. build the RTEMS app following the official guide, then you will get hello.exe(for example)
    2. Create a Vitis project, we call it hello project. 
    3. Test the vitis project and debug it, if it can successfully output "hello world" in serial console,    
        this means the project and debug configure are both ok.   
        Note: the debug type select "Single Application Debug", without GDB.   
    4. Set the debug configure for hello project in Vitis. Just change the Application section.    
        ``` Debug configuration --> Application --> Browse --> select the RTEMS app hello.exe. ```   
        Note : change the ".elf" to ".exe" at the right bottom of the file select window.
    5. Start debugging RTEMS program just like debugging the Vitis hello project. 
    6. Creating a c project using Makefile project template in vitis and set the project location in path of    
        "$RTEMS_HOME/src/rtems", so that the source code can be followed when debuging RTEMS program.    

***
### Problem
    Cannot read symbol data. Invalid abbreviation table. Error reading DWARF data When debuging following   
    the above steps, this error may appear. The reason is that RTEMS gcc version and the Xilinx Vistis GDB   
    version are not compatiable. The solution is upgrade your Vitis version or downgrade RTEMS version.   
    RTEMS6 and Vitis2022.2 can work. RTEMS5 and Vitis2020.1 can also work. Other versions are not tested.      

