#include <LPC11xx.h>

namespace {
  void write(char data) {
    while (!(LPC_UART->LSR & (1<<5)));
    LPC_UART->THR = data;
  }
  
  void write(uint32_t data) {
    static char stack[10];
    uint8_t p = 0;
    
    do {
      stack[p++] = '0' + (data % 10);
    } while ((data /= 10) != 0);
    
    for (int i=p-1; i>=0; --i) write(stack[i]);
  }
  
  void write(const char * data) {
    while (*data != '\0') write(*data++);
  }

  volatile uint32_t count = 0;
}

extern "C" {
  void PIOINT1_IRQHandler(void) {
    if (!(LPC_GPIO1->MIS & (1<<0))) return;
    LPC_GPIO1->IC |= (1<<0);
    if (!(LPC_GPIO1->DATA & (1<<0))) ++::count;
  }
  
  void TIMER16_0_IRQHandler(void) {
    if (!(LPC_TMR16B0->IR & (1<<2))) return;
    LPC_TMR16B0->IR = (1<<2);
    write(::count);
    write("\r\n");
    if (::count > 1000) LPC_GPIO1->DATA &= ~(1<<8);
    else                LPC_GPIO1->DATA |=  (1<<8);
    ::count = 0;
  }
}
