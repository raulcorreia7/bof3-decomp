#include "area098_13.h"

MATCH void func_801F3D98(void) {
    u8 remaining;

    SELF(Actor)->screen_x -= 0x10;
    SELF(Actor)->unk_03 -= 8;
    Area_UpdateSpawnSlots();
    Area_DrawYellowLine(&SELF(Actor)->unk_18, &SELF(Actor)->pos.x, SELF(Actor)->unk_03);
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}
