#include "game_00.h"

MATCH void func_801C56E4(void) {
    u8     index;
    Actor* work;
    Actor* state;

    work            = TASK(Actor);
    work->direction = (work->direction ^ 0x4);
    index           = 59;
    if (TASK(Actor)->direction == FACING_RIGHT) {
        index = 58;
    }
    Script_Request(index);
    GFX_PaletteLoad((TASK(Actor)->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    Actor_ClearVelocity();
    state                    = TASK(Actor);
    state->gravity           = -8;
    state->header.mode       = 2;
    TASK(Actor)->header.step = 3;
    TASK(Actor)->unk_03      = 3;
}
