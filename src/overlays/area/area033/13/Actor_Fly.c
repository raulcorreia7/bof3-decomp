#include "area033_13.h"

/* Moves the actor along its flight path. */
/* func_801F445C */
MATCH void Actor_Fly(void) {
    u8* scratch;
    u8* work;

    scratch = SELF(u8);
    if (scratch[0x0B] != 0) {
        if ((scratch[0] & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch[0] & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch[0x0B] = 1;
    }

    work = SELF(u8);
    *(s32*)(work + 0x34) += *(s32*)(work + 0x0C);
    *(s32*)(work + 0x38) += *(s32*)(work + 0x10);
    Script_AnimStepLoop();
    Area_AddGridActor();
}
