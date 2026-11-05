#include "area091_13.h"

MATCH void func_801F2DB0(void) {
    if (*D_80144F5A != 6 && *D_80144F5A != 3) {
        g_CurrentActor->interaction_flags &= 0xFE;
        return;
    }
    if (Item_Count(ITEM_CAT_ITEM, ITEM_FAERIE_TIARA, 0) == 0) {
        g_AreaSceneMode = 1;
        g_CurrentActor->interaction_flags &= 0xFE;
        SND_PlayCue(0x201U);
        return;
    }
    Game_SetScriptActive();
    g_Task->unk_04 += 1;
}
