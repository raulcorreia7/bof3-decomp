#include "area116_13.h"

MATCH s32 func_801F2E68(void) {
    /* FAKE: retail reads Game_SetScriptActive as s32(void). */
    ((s32 (*)(void))Game_SetScriptActive)();
    g_SceneEventMode      = 4;
    g_SceneEventSelection = 8;
    return 0;
}
