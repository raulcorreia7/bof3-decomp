#include "engine/game/00/game_00.h"

/* func_801C5474 */
/* Moves the actor while the exit timer counts down; at zero it returns the member to the walk mode and returns 1. */
MATCH s32 Area_ClimbDismountExit(void) {
    Actor* actor;
    Actor* actor_b;
    u8     frames;
    actor  = TASK(Actor);
    frames = actor->timer;
    if (frames == 0) {
        Script_Request(actor->direction);
        Actor_ClearVelocity();
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
        TASK(Actor)->unk_04 = 0;
        return 1;
    }
    actor->timer = (frames - 1);
    Actor_Move();
    actor_b = TASK(Actor);
    if (actor_b->timer == actor_b->unk_0A) {
        GFX_PaletteLoad(((actor_b->unk_05 << 6) + GAME_PALETTE_STAGE), 0);
    }
    Script_AnimStepLoop();
    return 0;
}
