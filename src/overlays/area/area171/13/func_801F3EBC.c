#include "area171_13.h"

MATCH s32 func_801F3EBC(void) {
    if (D_80143F03 == 3) {
        if (!SYS_TestFlag(g_SceneEventFlags, 0x74)) {
            Game_SetScriptActive();
            D_801448EB = 0x30;
            D_801448EC = 0;
            return 1;
        }
    }
    return 0;
}
