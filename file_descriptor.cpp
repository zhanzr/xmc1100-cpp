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
    return 0;
  }
	
  int fputc(int c, FILE *stream) {
		XMC_UART_CH_Transmit(XMC_UART0_CH1, c);
		return c;
  }
	
  int ferror(FILE *stream) {
		return 0;
  }
	
  long int ftell(FILE *stream) {
		return 0;
  }
	
  int fclose(FILE *f) {
    return 0;
  }
	
  int fseek(FILE *f, long nPos, int nMode) {
    return 0;
  }
	
  int fflush(FILE *f) {
    return 0;
  }
}
