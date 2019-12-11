#include <stdint.h>
#include "stm32f4xx_hal.h"

#define SYSMEM_RESET_VECTOR            0x1fff0004 //  0x1fffC804 -- orig	//STM32 App Note 2606 0x1ff00000
#define RESET_TO_BOOTLOADER_MAGIC_CODE 0xDEADBEEF
#define BOOTLOADER_STACK_POINTER       0x20002250

uint32_t dfu_reset_to_bootloader_magic;

void DfuCheck(void)
{
    if (dfu_reset_to_bootloader_magic == RESET_TO_BOOTLOADER_MAGIC_CODE)
    {
        void (*bootloader)(void) = (void (*)(void)) (*((uint32_t *) SYSMEM_RESET_VECTOR));
        dfu_reset_to_bootloader_magic = 0;
        __set_MSP(BOOTLOADER_STACK_POINTER);
        bootloader();
        while (42);
    }
    else
    {
        // SystemInit();
    }
}

void dfu_run_bootloader()
{
    dfu_reset_to_bootloader_magic = RESET_TO_BOOTLOADER_MAGIC_CODE;
    NVIC_SystemReset();
}
