#include "area149_13.h"

MATCH void func_801F3068(void) {
    if (g_AreaCameraOffsetZ == 0) {
        *g_ScriptVars = 0x14;
        SND_SEPlay(1);
        SELF(Actor)->unk_04++;
    }
    if (g_PartyActors[0].pos.x.fixed < g_AreaScrollTargetX + TO_COORD(2)) {
        g_PartyActors[0].unk_78 = 3;
    }
    func_801F3140(-2);
    g_ScriptState->cursor -= 2;
}
