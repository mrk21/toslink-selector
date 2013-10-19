SEARCH_DIR(.);

OUTPUT_FORMAT("elf32-littlearm");
OUTPUT_ARCH(arm);

ENTRY(_startup)


/* Memory Map */
MEMORY {
  flash (rx) : ORIGIN = 0x00000000, LENGTH = 32K
  sram (rwx) : ORIGIN = 0x10000000, LENGTH = 4k
}

__flash_start = ORIGIN(flash);
__flash_end = ORIGIN(flash) + LENGTH(flash);
__sram_start = ORIGIN(sram);
__sram_end = ORIGIN(sram) + LENGTH(sram);


/* Sections */
SECTIONS {
  .text : ALIGN(4) {
    KEEP(*(.isr_vector));
    *(.after_isr_vector);
    *(.text .text.*);
    *(.rodata .rodata.*);
  } > flash = 0xff
  
  __text_size = SIZEOF(.text);
  __text_start = ADDR(.text);
  __text_end = __text_start + __text_size;
  
  
  .data : ALIGN(4) {
    *(.data .data.*);
  } > sram AT > flash = 0xff
  
  __data_size = SIZEOF(.data);
  __data_start = ADDR(.data);
  __data_end = __data_start + __data_size;
  __data_source = LOADADDR(.data);
  
  
  .bss : ALIGN(4) {
    *(.bss .bss.*);
  } > sram
  
  __bss_size = SIZEOF(.bss);
  __bss_start = ADDR(.bss);
  __bss_end = __bss_start + __bss_size;
  
  
  .stack : ALIGN(4) {
    . += 1024;
  } > sram
  
  __stack_size = SIZEOF(.stack);
  __stack_start = ADDR(.stack);
  __stack_end = __stack_start + __stack_size;
  
  
  .heap : {} > sram
  
  __heap_start = ADDR(.heap);
  __heap_end = __sram_end;
  __heap_size = __heap_end - __heap_start;
}
