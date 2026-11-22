#include "area015_13.h"
#include "common/util.h"
#include "menu/gameui.h"

MATCH void func_801F2DBC(void) {
    s32 idx;

    idx                 = (g_FrameCount & 0x2) >> 1;
    TASK(Actor)->unk_0A = RANDOM_MASK(7);
    idx                 = idx * 2;
    Script_Request(D_801F40F8[idx]);
    TASK(Actor)->mirror = D_801F40F9[idx];
    TASK(Actor)->unk_04 = 1;
    g_ScriptState->cursor -= 2;
}
