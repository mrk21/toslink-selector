#include <LPC11xx.h>

namespace {
  void write(char data) {
    while (!(LPC_UART->LSR & (1<<5)));
    LPC_UART->THR = data;
  }
}

int main(void) {
  // uart
  {
    LPC_IOCON->PIO1_6 |= 0x01;
    LPC_IOCON->PIO1_7 |= 0x01;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
    LPC_SYSCON->UARTCLKDIV = 0x01;
    
    constexpr auto BAUDRATE = 9600;
    auto DL = (SystemCoreClock * LPC_SYSCON->SYSAHBCLKDIV) / (16 * BAUDRATE * LPC_SYSCON->UARTCLKDIV);
    LPC_UART->LCR |= (1<<7);
    LPC_UART->DLM = DL / 256;
    LPC_UART->DLL = DL % 256;
    LPC_UART->LCR &= ~(1<<7);
    LPC_UART->LCR = 0x03;
    LPC_UART->FCR = 0x07;
  }
  
  // toslink signal
  {
    LPC_GPIO1->DIR &= ~(1<<0);
    
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_SetPriority(EINT1_IRQn, 2);
    LPC_GPIO1->IS  &= ~(1<<0);
    LPC_GPIO1->IBE &= ~(1<<0);
    LPC_GPIO1->IEV &= ~(1<<0);
    LPC_GPIO1->IE  |=  (1<<0);
  }
  
  // clock
  {
    LPC_IOCON->PIO0_8 |= (1<<1);
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
    
    LPC_TMR16B0->PR = 36 - 1;
    LPC_TMR16B0->EMR |= (3<<4);
    LPC_TMR16B0->MCR |= (1<<6);
    NVIC_EnableIRQ(TIMER_16_0_IRQn);
    NVIC_SetPriority(TIMER_16_0_IRQn, 1);
    LPC_TMR16B0->TCR = 1;
  }
  
  // selector signal
  {
    LPC_GPIO1->DIR |= (1<<8);
  }
  LPC_GPIO1->DATA &= ~(1<<8);
  write('a');
  
  return 0;
}
