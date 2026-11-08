#include "area048_13.h"

MATCH void func_801F4864(void) {
    u8* counter;

    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_CharSlot[g_Game.members[0].chr.character_id] == 1) {
        counter = &D_8014686B;
        if (*counter < 8U) {
            *counter += 1;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0D));
    }
}
