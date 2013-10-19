#include <system_LPC11xx.h>


extern void (* const _isr_vector[])(void);
extern int main(void);

void _startup(void);
void _init_data(void);
void _init_bss(void);


// Linker Definition Symbols
extern void __stack_end(void);
extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_source;
extern uint32_t __bss_start;
extern uint32_t __bss_end;


// Handers
__attribute__ ((weak)) void NMI_Handler      (void);
__attribute__ ((weak)) void HardFault_Handler(void);
__attribute__ ((weak)) void SVC_Handler      (void);
__attribute__ ((weak)) void PendSV_Handler   (void);
__attribute__ ((weak)) void SysTick_Handler  (void);
__attribute__ ((weak)) void IntDefaultHandler(void);

void CAN_IRQHandler      (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void SSP1_IRQHandler     (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void I2C_IRQHandler      (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void TIMER16_0_IRQHandler(void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void TIMER16_1_IRQHandler(void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void TIMER32_0_IRQHandler(void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void TIMER32_1_IRQHandler(void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void SSP0_IRQHandler     (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void UART_IRQHandler     (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void ADC_IRQHandler      (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void WDT_IRQHandler      (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void BOD_IRQHandler      (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void PIOINT3_IRQHandler  (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void PIOINT2_IRQHandler  (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void PIOINT1_IRQHandler  (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void PIOINT0_IRQHandler  (void) __attribute__ ((weak, alias ("IntDefaultHandler")));
void WAKEUP_IRQHandler   (void) __attribute__ ((weak, alias ("IntDefaultHandler")));


// ISR vector
__attribute__ ((section(".isr_vector"))) void (* const _isr_vector[])(void) = {
  __stack_end,
  _startup,
  
  NMI_Handler,
  HardFault_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  SVC_Handler,
  0,
  0,
  PendSV_Handler,
  SysTick_Handler,
  
  // Wakeup sources for the I/O pins:
  //   PIO0 (0:11)
  //   PIO1 (0)
  WAKEUP_IRQHandler,                      // PIO0_0  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_1  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_2  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_3  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_4  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_5  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_6  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_7  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_8  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_9  Wakeup
  WAKEUP_IRQHandler,                      // PIO0_10 Wakeup
  WAKEUP_IRQHandler,                      // PIO0_11 Wakeup
  WAKEUP_IRQHandler,                      // PIO1_0  Wakeup
  
  CAN_IRQHandler,
  SSP1_IRQHandler,
  I2C_IRQHandler,
  TIMER16_0_IRQHandler,                   // CT16B0 (16-bit Timer 0)
  TIMER16_1_IRQHandler,                   // CT16B1 (16-bit Timer 1)
  TIMER32_0_IRQHandler,                   // CT32B0 (32-bit Timer 0)
  TIMER32_1_IRQHandler,                   // CT32B1 (32-bit Timer 1)
  SSP0_IRQHandler,                        // SPI/SSP0 Interrupt
  UART_IRQHandler,                        // UART0
  
  0,
  0,
  
  ADC_IRQHandler,                         // ADC   (A/D Converter)
  WDT_IRQHandler,                         // WDT   (Watchdog Timer)
  BOD_IRQHandler,                         // BOD   (Brownout Detect)
  0,
  PIOINT3_IRQHandler,                     // PIO INT3
  PIOINT2_IRQHandler,                     // PIO INT2
  PIOINT1_IRQHandler,                     // PIO INT1
  PIOINT0_IRQHandler,                     // PIO INT0
};


// Startup
__attribute__ ((section(".after_isr_vector"))) void _startup(void) {
  _init_data();
  _init_bss();
  SystemInit();
  main();
  while (1);
}

__attribute__ ((section(".after_isr_vector"))) void _init_data(void) {
  uint32_t * data = &__data_start;
  uint32_t * source = &__data_source;
  while (data < &__data_end) {
    *data++ = *source++;
  }
}

__attribute__ ((section(".after_isr_vector"))) void _init_bss(void) {
  uint32_t * bss = &__bss_start;
  while (bss < &__bss_end) {
    *bss++ = 0;
  }
}


// Default hander implementation.
__attribute__ ((section(".after_isr_vector"))) void NMI_Handler      (void) { while (1); }
__attribute__ ((section(".after_isr_vector"))) void HardFault_Handler(void) { while (1); }
__attribute__ ((section(".after_isr_vector"))) void SVC_Handler      (void) { while (1); }
__attribute__ ((section(".after_isr_vector"))) void PendSV_Handler   (void) { while (1); }
__attribute__ ((section(".after_isr_vector"))) void SysTick_Handler  (void) { while (1); }
__attribute__ ((section(".after_isr_vector"))) void IntDefaultHandler(void) { while (1); }
