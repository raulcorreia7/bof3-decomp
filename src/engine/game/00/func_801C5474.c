#include "game_00.h"

MATCH s32 func_801C5474(void) {
    Actor* work;
    Actor* state;
    u8     countdown;
    work      = TASK(Actor);
    countdown = work->timer;
    if (countdown == 0) {
        Script_Request(work->direction);
        Actor_ClearVelocity();
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
        TASK(Actor)->unk_04 = 0;
        return 1;
    }
    work->timer = (countdown - 1);
    Actor_Move();
    state = TASK(Actor);
    if (state->timer == state->unk_0A) {
        GFX_PaletteLoad(((state->unk_05 << 6) + GAME_PALETTE_STAGE), 0);
    }
    Script_AnimStepLoop();
    return 0;
}
