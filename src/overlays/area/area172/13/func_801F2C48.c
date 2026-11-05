#include "area172_13.h"

MATCH void func_801F2C48(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = (u8*)g_Task;
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = (u8*)g_Task;
    second[9] = 0x5A;

    third    = (u8*)g_Task;
    third[1] = 1;
}
