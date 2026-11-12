#include "area075_13.h"

MATCH void func_801F3530(void) {
    s32 step = !(g_FrameCount & 0x3);

    g_ActorSlots[D_801F58CE[0]].scene_step -= step;
    g_ActorSlots[D_801F58CE[1]].scene_step -= step;
    if (g_ScriptVars[0] < 0x20) {
        g_ScriptState->cursor -= 2;
    }
}
