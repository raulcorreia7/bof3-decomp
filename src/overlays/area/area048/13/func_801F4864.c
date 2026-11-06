#include "area048_13.h"

MATCH void func_801F4864(void) {
    u8* counter;

    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_CharSlot[D_80145F09] == 1) {
        counter = &D_8014686B;
        if (*counter < 8U) {
            *counter += 1;
        }
        SND_PlayCue(0x20DU);
    }
}
