#include "area091_13.h"

MATCH void func_801F2DB0(void) {
    if (*D_80144F5A != 6 && *D_80144F5A != 3) {
        g_CurrentActor->flags_74 &= 0xFE;
        return;
    }
    if (Party_CountItem(0, 0x57, 0) == 0) {
        g_AreaSceneMode = 1;
        g_CurrentActor->flags_74 &= 0xFE;
        SND_PlayCue(0x201U);
        return;
    }
    Game_SetScriptActive();
    g_SpadWork->unk_04 += 1;
}
