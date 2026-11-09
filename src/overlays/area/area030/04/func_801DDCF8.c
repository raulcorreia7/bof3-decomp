#include "area030_04.h"

/* When halfword `g_UiWindowEffectBusy` is clear, increments byte `D_8014403D`
 * and arms the scratchpad work object: byte 0x02 = 1, byte 0x03 = 0. */
MATCH void func_801DDCF8(void) {
    u8* counter;

    if (WINDOW_EFFECT_IDLE()) {
        counter = &D_8014403D;
        *counter += 1;
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0;
    }
}
