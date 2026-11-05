#include "area030_04.h"

/* Resets the AREA030 scratchpad record for the next state: clears the
 * state, clip, and draw fields, primes the colour step and depth slots, marks
 * the record busy and advances the state byte. */
MATCH void func_801D42E4(void) {
    FishingState* work;
    FishingState* advanced;

    g_SpadWork->direction_08 = 0;
    g_SpadWork->unk_06       = 0;
    g_SpadWork->option_flags = 0x80;
    ((u8*)g_SpadWork)[9]     = 4;
    g_SpadWork->unk_0A       = 0;

    work                 = FISHING_STATE;
    work->saved_index_0B = 0;
    advanced             = FISHING_STATE;

    *(u32*)((u8*)work + 0x34) = 0;
    work->y_38.pos_y          = 0;
    *(u32*)((u8*)work + 0x3C) = 0;
    work->pos_x_0C            = 0;
    work->cursor_10           = 0;

    *(u16*)((u8*)advanced + 0x2C) = 0xFFFF;
    advanced->handler_index_01    = (u8)(advanced->handler_index_01 + 1);
}
