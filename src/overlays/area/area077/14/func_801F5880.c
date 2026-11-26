#include "area077_14.h"

/* Matches the two cell coordinates and the scene mode against the payload's two trigger
 * records, sets the matched record's flag on the scene event bank and queues SE 0x201. */
MATCH s32 func_801F5880(s32 x, s32 y) {
    s32 i;
    s32 off;
    u32 id0;
    u32 id1;
    u8* mode;

    if (SYS_TestFlag(D_80144EB8, 0x2C) != 0) {
        return 0;
    }
    i    = 0;
    id0  = x & 0xFF;
    id1  = y & 0xFF;
    mode = &g_Game.members[0].facing;
    off  = 0;
    for (; i < 2; i++, off += 4) {
        if (id0 == D_801F6B14[off] && id1 == D_801F6B15[off] && D_801F6B16[off] == *mode) {
            break;
        }
    }
    if (i == 2) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F6B17[i * 4]);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    Scene_StartToggleLock(0xF);
    return 1;
}
