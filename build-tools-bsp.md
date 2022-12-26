### Build compile tools
1. Install needed libs under ubuntu(18.04.2)   
   ``` sudo apt install build-dep build-essential gcc-defaults g++ gdb unzip pax bison flex texinfo python3-dev libpython2-dev libncurses5-dev zlib1g-dev```    
   ``` sudo apt-get install git```
   ``` sudo ln -s /usr/bin/python3 /usr/bin/python```
   If some package can not found, just skip.
   
2. Add environment path in /etc/profile for RTEMS_HOME   
   add :  ``` export RTEMS_HOME=/xxxx/quick-start ```     
   
3. Build tools
 
 ``` cd $RTEMS_HOME/src/rsb/rtems```   
 ``` ../source-builder/sb-set-builder --prefix=$RTEMS_HOME/rtems/6 6/rtems-arm ```     

*** 

### Build BSP 
#### RTEMS6
1. enter the source path of rtems    
  ``` cd $RTEMS_HOME/quick-start/src/rtems ```   
2. Create a sh file(build-bsp.sh)
  ``` touch build-bsp.sh```   
  ``` chomd +x build-bsp.sh ```    
3. Input the following commands to build-bsp.sh file   
 ``` #!/bin/sh   ```    
 ``` echo "[sparc/xilinx_aynqmp_ultra96]" > config.ini ```    
 ``` echo "BUILD_TESTS = True" >> config.ini ```    
 ``` echo "BUILD_SAMPLES=True" >> config.ini ```    
 ``` echo "RTEMS_DEBUG=True" >> config.ini ```    
 ``` ./waf configure --prefix=/home/li/Documents/RTEMS/quick-start/rtems/6 && ```     
 ``` ./waf && ```   
 ``` ./waf install && ```   
 ``` echo "Build finished!" ```      
  
4. Execute the sh file   
 ``` ./build-bsp.sh ```    

 
#### RTEMS5   
 1. Create a build folder   
 ``` mkdir -p $RTEMS_HOME//build/zedboard ```    
 2. Execute following command to configure BSP:   
 ``` $RTEMS_HOME/src/rtems/configure --prefix=$RTEMS_HOME/rtems/5 --enable-maintainer-mode --target=arm-rtems5 --enable-rtemsbsp=xilinx_zynq_zedboard   --enable-tests --enable-rtems-debug ```     
 3. make and make install   
  ``` make && make install ```   
