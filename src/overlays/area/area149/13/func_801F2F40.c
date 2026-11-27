#include "area149_13.h"

MATCH void func_801F2F40(void) {
    if (g_AreaCameraOffsetZ < 0x880) {
        g_PartyActors[0].unk_78 = 1;
        g_ScriptVars[0]         = 10;
        SND_SEPlay(1);
        SELF(Actor)->unk_04++;
    }
    func_801F3140(-4);
    g_ScriptState->cursor -= 2;
}
