#include "area091_13.h"

MATCH void func_801F3504(void) {
    g_SpadWork->unk_0A -= 1;
    if (g_SpadWork->unk_0A == 0) {
        D_80146867         = 1;
        g_SpadWork->unk_04 = 0;
        g_CurrentActor->flags_74 &= 0xFE;
        g_CurrentActor->unk_7E += 1;
        Game_ClearScriptActive();
    }
    func_801F2ED4(g_SpadWork->unk_0A * 0xA, 0xFF);
}
