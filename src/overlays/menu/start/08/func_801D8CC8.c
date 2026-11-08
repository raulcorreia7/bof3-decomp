#include "start_08.h"

MATCH void func_801D8CC8(void) {
    u8* counter;

    Menu_DrawClutStrip(D_80144953);
    counter = &D_80148654;
    *counter -= 1;
    if (*counter == 0) {
        func_801D9664();
        g_BattleListCursor          = D_801ED891;
        g_MenuPanelTasks[17].unk_0A = D_801ED890;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        *counter = 7;
        D_80148652 += 1;
    }
}
