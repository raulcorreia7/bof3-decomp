#include "area170_13.h"

MATCH s32 func_801F5698(void) {
    s8* flags;

    Game_SetScriptActive();
    flags                  = &g_SceneEventState.mode;
    *flags                 = 0x25;
    g_SceneEventState.step = 0x28;
    SYS_ClearFlag(flags + 0x63D, 126U);
    return 1;
}
