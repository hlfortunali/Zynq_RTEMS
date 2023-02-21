## Shell demo
  Use the sample of "fileio" to test the RTEMS shell.
  

## Problem
 in 5.1 version the following function has "#if 0" macro, so that the shell initialization will fail.    
 The macro need to be set as 1 and add the declearation of "zynq_uart_set_attributes" function.   
 Then configure the bsp and compile again.    
 
 ```
  static bool zynq_uart_set_attributes(
  rtems_termios_device_context *context,
  const struct termios *term
  )
  {
  #if 0
  volatile zynq_uart *regs = zynq_uart_get_regs(minor);
  uint32_t brgr = 0;
  uint32_t bauddiv = 0;
  int rc;

  rc = zynq_cal_baud_rate(115200, &brgr, &bauddiv, regs->mode);
  if (rc != 0)
    return rc;

  regs->control &= ~(ZYNQ_UART_CONTROL_RXEN | ZYNQ_UART_CONTROL_TXEN);
  regs->baud_rate_gen = ZYNQ_UART_BAUD_RATE_GEN_CD(brgr);
  regs->baud_rate_div = ZYNQ_UART_BAUD_RATE_DIV_BDIV(bauddiv);
  regs->control |= ZYNQ_UART_CONTROL_RXEN | ZYNQ_UART_CONTROL_TXEN;

  return true;
  #else
  return false;
  #endif
  }
  
