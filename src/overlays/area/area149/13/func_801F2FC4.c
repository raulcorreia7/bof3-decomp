#include "area149_13.h"

MATCH void func_801F2FC4(void) {
    if (g_AreaViewOffsetZ < 0x680) {
        *g_ScriptVars = 0xF;
        SND_PlayCue(0U);
        g_SpadWork->unk_04 += 1;
    }
    if (D_80147A8C < (g_AreaScrollTargetX + 0x20000)) {
        D_80147AD0 = 3;
    }
    func_801F3140(-3);
    g_ScriptState->cursor -= 2;
}
