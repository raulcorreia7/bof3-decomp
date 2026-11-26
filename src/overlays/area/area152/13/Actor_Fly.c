#include "area152_13.h"

/* Moves the actor along its flight path. */
/* func_801F43E8 */
MATCH void Actor_Fly(void) {
    Actor* scratch;
    u8*    work;

    scratch = SELF(Actor);
    if (scratch->param.unk_0B != 0) {
        if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch->param.unk_0B = 1;
    }

    work = SELF(u8);
    *(s32*)(work + 0x34) += *(s32*)(work + 0x0C);
    *(s32*)(work + 0x38) += *(s32*)(work + 0x10);
    Script_AnimStepLoop();
    Area_AddGridActor();
}
