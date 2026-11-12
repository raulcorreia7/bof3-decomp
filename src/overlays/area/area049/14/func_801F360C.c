#include "area049_14.h"

MATCH void func_801F360C(void) {
    ActorSlot* actor_slot;
    s32        actor_index;

    if (g_Game.members[0].chr.character_id == CHAR_ID_MOMO) {
        actor_index = func_8019601C() & BYTE_MASK;
        if (actor_index != GAME_NONE) {
            actor_slot               = &g_ActorSlots[actor_index];
            actor_slot->header.flags = ACTOR_FLAG_IN_USE;
            actor_slot->type         = 0x6C;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x09));
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        Area_SetCellCode(11, 85, 0xC0);
        Area_SetCellCode(12, 85, 0xC0);
        D_80146874    = 4;
        *g_ScriptVars = 0;
        D_80146875    = 0x1E;
        return;
    }
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
}
