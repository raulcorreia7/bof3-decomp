#include "area012_13.h"

MATCH s32 func_801F2C04(void) {
    if (!SYS_TestFlag(g_SceneFlags, 14)) {
        g_ScriptState->cursor -= 2;
    }
}
