#include "area030_04.h"

/* Increments the shared state byte at 0x801440B1, reports it through func_8014D8D4 with argument 1. */

MATCH void func_801DA5F8(void) {
    u8* state_byte = &D_801440B1;

    (*state_byte)++;
    Actor_RequestScript(1);
    g_Task->unk_03 = 1;
}
