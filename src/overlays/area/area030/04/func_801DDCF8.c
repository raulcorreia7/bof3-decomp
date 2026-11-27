#include "area030_04.h"

/* When halfword `g_UIWindowEffectBusy` is clear, increments byte `D_8014403D`
 * and arms the scratchpad work object: byte 0x02 = 1, byte 0x03 = 0. */
MATCH void func_801DDCF8(void) {
    u8* counter;

    if (WINDOW_EFFECT_IDLE()) {
        counter = &g_SpawnedActors[1].header.mode;
        *counter += 1;
        SELF(FishingState)->mode_index = 1;
        SELF(FishingState)->sub_index  = 0;
    }
}
