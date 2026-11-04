#include "area188_13.h"

MATCH void func_801F4840(void) {
    if ((u32)(g_SpadWork->y.fixed + g_FacingSteps[g_SpadWork->direction_08 & 7].y) <= (u32)(D_801F6898[D_801448ED] << 16)) {
        g_ScriptState->unk_07 = 1;
        func_801ABBA8(g_ScriptState, 5);
        g_ScriptState->cursor -= 2;
    }
}
