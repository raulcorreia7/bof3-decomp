#include "area030_04.h"

/* Resets the AREA030 scratchpad panel: it clears the state flag byte,
 * rewinds the panel vertical offset to -0x19, and advances the state byte. */
MATCH void func_801D3650(void) {
    u8* ptr;
    u8* ptr2;

    ptr                 = (u8*)g_Task;
    ptr[7]              = 0;
    ptr2                = (u8*)g_Task;
    *(s16*)(ptr + 0x30) = -0x19;
    ptr2[1]             = (u8)(ptr2[1] + 1);
}
