#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <XMC1100.h>
#include <xmc_scu.h>
#include <xmc_rtc.h>
#include <xmc_uart.h>
#include <xmc_gpio.h>

//Re-implement any functions that require re-implementation.
namespace std {
  struct __FILE {
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
  };
	
  FILE __stdout;
  FILE __stdin;
  FILE __stderr;
  int fgetc(FILE *f) {
    /* Your implementation of fgetc(). */
    return 0;
  }
	
  int fputc(int c, FILE *stream) {
		XMC_UART_CH_Transmit(XMC_UART0_CH1, c);
		return c;
  }
	
  int ferror(FILE *stream) {
    /* Your implementation of ferror(). */
  }
	
  long int ftell(FILE *stream) {
    /* Your implementation of ftell(). */
  }
	
  int fclose(FILE *f) {
    /* Your implementation of fclose(). */
    return 0;
  }
	
  int fseek(FILE *f, long nPos, int nMode) {
    /* Your implementation of fseek(). */
    return 0;
  }
	
  int fflush(FILE *f) {
    /* Your implementation of fflush(). */    
    return 0;
  }
}
