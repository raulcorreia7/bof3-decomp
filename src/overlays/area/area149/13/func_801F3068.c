#include "area149_13.h"

MATCH void func_801F3068(void) {
    if (g_AreaViewOffsetZ == 0) {
        *g_ScriptVars = 0x14;
        SND_PlayCue(1);
        g_SpadWork->unk_04++;
    }
    if (D_80147A8C < g_AreaScrollTargetX + 0x20000) {
        D_80147AD0 = 3;
    }
    func_801F3140(-2);
    g_ScriptState->cursor -= 2;
}
