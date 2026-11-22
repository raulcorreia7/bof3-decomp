#include "area098_13.h"

MATCH void func_801F3D98(void) {
    u8 remaining;

    TASK(Actor)->screen_x -= 0x10;
    TASK(Actor)->unk_03 -= 8;
    Area_UpdateSpawnSlots();
    Area_DrawYellowLine(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, TASK(Actor)->unk_03);
    ACTOR_COUNT_DOWN(TASK(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}
