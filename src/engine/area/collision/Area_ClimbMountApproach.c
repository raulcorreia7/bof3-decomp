#include "engine/game/00/game_00.h"

/* func_801C4E14 */
/* Moves the actor while the approach timer counts down and returns nonzero once it ends, with the facing animation requested. */
MATCH s32 Area_ClimbMountApproach(void) {
    Actor* actor;
    Actor* actor_b;
    u8     frames;
    u8     slot;
    s32    ended;

    actor  = TASK(Actor);
    frames = actor->timer;
    ended  = 0;
    if (frames != 0) {
        actor->timer = (frames - 1);
        Actor_Move();
        actor_b = TASK(Actor);
        if (actor_b->timer == actor_b->unk_0A) {
            slot                                            = actor_b->unk_05;
            g_GfxPalettePending                             = 1;
            *(u16*)(MEM_PTR(u8, 0x8003963Eu) + (slot << 6)) = 0;
        }
    } else {
        ended = 1;
        Script_Request(actor->direction);
        TASK(Actor)->unk_0A = 4U;
    }
    Script_AnimStepLoop();
    return ended;
}
