#include "area149_13.h"

MATCH void func_801F2FC4(void) {
    if (g_AreaCameraOffsetZ < 0x680) {
        *g_ScriptVars = 0xF;
        SND_SEPlay(0U);
        SELF(Actor)->unk_04 += 1;
    }
    if (g_PartyActors[0].pos.x.fixed < (g_AreaScrollTargetX + TO_COORD(2))) {
        g_PartyActors[0].unk_78 = 3;
    }
    func_801F3140(-3);
    g_ScriptState->cursor -= 2;
}
