# Build compile tools
### 1. Install needed libs under ubuntu(18.04.2)   
   ``` sudo apt install build-dep build-essential gcc-defaults g++ gdb unzip pax bison flex texinfo python3-dev libpython2-dev libncurses5-dev zlib1g-dev```    
   ``` sudo apt-get install git```
   ``` sudo ln -s /usr/bin/python3 /usr/bin/python```
   If some package can not found, just skip.
   
### 2. Add environment path in /etc/profile for RTEMS_HOME   
   add :  ``` export RTEMS_HOME=/xxxx/quick-start ```     
   
### 3. Build tools
 
 ``` cd $RTEMS_HOME/src/rsb/rtems```   
 ``` ../source-builder/sb-set-builder --prefix=$RTEMS_HOME/rtems/6 6/rtems-arm ```     

 Then, add tools to PATH:   
 add following line in /etc/profile   
 ``` export PATH=RTEMS_HOME/rtems/6/bin:$PATH ```    

*** 
***

# Build BSP 
### RTEMS6
#### 1. enter the source path of rtems    
  ``` cd $RTEMS_HOME/quick-start/src/rtems ```   
#### 2. Create a sh file(build-bsp.sh)
  ``` touch build-bsp.sh```   
  ``` chomd +x build-bsp.sh ```    
#### 3. Input the following commands to build-bsp.sh file   
      #!/bin/sh   
      echo "[arm/xilinx_zynq_zedboard]" > config.ini   
      echo "BUILD_TESTS = True" >> config.ini 
      echo "BUILD_SAMPLES=True" >> config.ini     
      echo "RTEMS_DEBUG=True" >> config.ini     
      echo "OPTIMIZATION_FLAGS = -O0 -g3 -fdata-sections -ffunction-sections" >> config.ini
      echo "ZYNQ_CLOCK_UART = 100000000" >> config.ini
      echo "BSP_ARM_A9MPCORE_PERIPHCLK = 333333334" >> config.ini
      ./waf configure --prefix=$RTEMS_HOME/rtems/6 &&   
      ./waf &&   
      ./waf install &&   
      echo "\nBuild finished!\n"    
      
   ###### Note：   
          The option like "BUILD_TESTS" can be checked via "./waf bspdefaults >> defaults.log" command.   
          Then search "[arm/xilinx_zynq_zedboard]" in defaults.log file, the options are listed in this   
          section. Then add option config in config.ini.
          
     
  
#### 4. Execute the sh file   
 ``` ./build-bsp.sh ```    


### RTEMS5   
 #### 1. Create a build folder   
 ``` mkdir -p $RTEMS_HOME/build/zedboard ```     
 
 #### 2. Change zynq zedboard periphral clock and uart clock frequency   
    1> in c/src/lib/libbsp/arm/xilinx_zynq folder, find file named "configure.ac".    
         ``` RTEMS_BSPOPTS_SET([BSP_ARM_A9MPCORE_PERIPHCLK],[xilinx_zynq_zedboard*],[666666667U])     line 32.    
         RTEMS_BSPOPTS_SET([ZYNQ_CLOCK_UART],[xilinx_zynq_zedboard*],[50000000UL])                line 37   ```   
       Change the 666666667U to 333333333U. Because the periphral clock frequency is half the core frequency.  
       Change the 50000000UL to 100000000UL. Because the uart clock is set 100000000UL by default.
    
    2> in c/src/lib/libbsp/arm/xilinx_zynq folder, find file named "configure".    
           ```  BSP_ARM_A9MPCORE_PERIPHCLK=${BSP_ARM_A9MPCORE_PERIPHCLK-666666667U} ;   line 4627   
            ZYNQ_CLOCK_UART=${ZYNQ_CLOCK_UART-50000000UL} ;                       line 4652 ```   
       And also change 666666667U to 333333333U and 50000000UL to 100000000UL.   Then save all changed files.

 #### 3. Enter the folder created in step 1 and Execute following command to configure BSP:   
 ``` $RTEMS_HOME/src/rtems/configure  --prefix=$RTEMS_HOME/rtems/5 --enable-maintainer-mode --target=arm-rtems5 --enable-rtemsbsp=xilinx_zynq_zedboard    --enable-tests --enable-rtems-debug CFLAGS_FOR_TARGET="-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9 -O0 -g3 -ffunction-sections -fdata-sections -Wall -Wmissing-prototypes -Wimplicit-function-declaration -Wstrict-prototypes -Wnested-externs"```    
 
 Note: the "-O0 -g3" flags are used to turn off compile optimization. So that the RTEMS kernel can be debugged. The default flag is "-O2 -g". 
   
 
 #### 4. make and make install   
  ``` make && make install ```   
  
  ***
  ***
# Build Application
reference to   https://ftp.rtems.org/pub/rtems/releases/5/5.1/docs/html/user/start/app.html

Need change bsp : ./waf configure --rtems=$HOME/quick-start/rtems/5 --rtems-bsp=arm/xilinx_zynq_zedboard
