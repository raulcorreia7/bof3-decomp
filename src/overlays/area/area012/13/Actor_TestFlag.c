#include "area012_13.h"

/* func_801F2C04 */
MATCH s32 Actor_TestFlag(void) {
    if (!SYS_TestFlag(g_SceneFlags, 14)) {
        g_ScriptState->cursor -= 2;
    }
}
