#include "area091_13.h"

MATCH void func_801F2DB0(void) {
    if (*g_PartyFieldOrder != 6 && *g_PartyFieldOrder != 3) {
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        return;
    }
    if (Item_Count(ITEM_CAT_ITEM, ITEM_FAERIE_TIARA, 0) == 0) {
        g_AreaSceneMode = 1;
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
        return;
    }
    Game_SetScriptActive();
    g_Task->unk_04 += 1;
}
