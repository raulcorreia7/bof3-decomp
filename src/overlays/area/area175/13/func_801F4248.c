#include "area175_13.h"

MATCH void func_801F4248(void) {
    void** scratchpad;
    void*  work;

    scratchpad            = SP_PTR(void*, 0u);
    work                  = scratchpad[0x44u / sizeof(void*)];
    FIELD(u8, work, 0xAu) = 0x20;
    work                  = g_Task;
    FIELD(u8, work, 0x4u) = 1;
}
