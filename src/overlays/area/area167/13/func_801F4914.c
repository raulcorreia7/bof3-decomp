#include "area167_13.h"

/* Sets the flag bit of the trigger record that matches the two cell coordinates and starts scene event 0x20. */
MATCH s32 func_801F4914(s32 x, s32 y) {
    s32 i;
    s32 off;
    u8* mode;

    i = 0;
    x &= BYTE_MASK;
    y &= BYTE_MASK;
    mode = &D_80145E98;
    off  = 0;
    for (; i <= 0; i++, off += 4) {
        if (x == D_801F68B4[off] && y == D_801F68B4[off + 1] && (D_801F68B4[off + 2] & 0xF) == *mode) {
            break;
        }
    }
    if (i == 1) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F68B4[i * 4 + 3]);
    Game_SetScriptActive();
    g_SceneEventMode = 0x20;
    g_SceneEventStep = 5;
    return 1;
}
