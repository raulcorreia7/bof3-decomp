#include "area030_04.h"

/* Resets the AREA030 scratchpad record for the next state: clears the
 * state, clip, and draw fields, primes the colour step and depth slots, marks
 * the record busy and advances the state byte. */
MATCH void func_801D42E4(void) {
    u8* record;
    u8* state;

    g_SpadWork->direction_08 = 0;
    g_SpadWork->unk_06       = 0;
    g_SpadWork->option_flags = 0x80;
    g_SpadWork->unk_09       = 4;
    g_SpadWork->unk_0A       = 0;

    record      = (u8*)g_SpadWork;
    record[0xB] = 0;
    state       = (u8*)g_SpadWork;

    *(u32*)(record + 0x34) = 0;
    *(u32*)(record + 0x38) = 0;
    *(u32*)(record + 0x3C) = 0;
    *(u32*)(record + 0xC)  = 0;
    *(u32*)(record + 0x10) = 0;

    *(u16*)(state + 0x2C) = 0xFFFF;
    state[1]              = (u8)(state[1] + 1);
}
