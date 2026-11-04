#include "area149_13.h"

MATCH void func_801F2F40(void) {
    if (g_AreaViewOffsetZ < 0x880) {
        D_80147AD0     = 1;
        g_ScriptVars[0] = 10;
        SND_PlayCue(1);
        g_SpadWork->unk_04++;
    }
    func_801F3140(-4);
    g_ScriptState->cursor -= 2;
}
