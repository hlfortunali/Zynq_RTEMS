# zynq_RTEMS
RTEMS demo for zynq 7010


## console baudrate problem
As the default baudrate is not the same as Alinx 7010 board, so we need to change the cpu clock frequency and uart clock reference in :  
opta9periphclk.yml and opta9periphclk.yml and optclkuart.yml  
Then usr ./waf tool to compile the BSP again.


## to be continue ...
