#include "area109_13.h"

MATCH s32 func_801F2D78(s32 arg0, s32 arg1) {
    s32 roll;
    u8* flag_id;

    if ((arg0 & 0xFF) != 0x1C) {
        return 0;
    }
    if ((arg1 & 0xFF) != 6) {
        return 0;
    }
    if (D_80145E98 != 3) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    flag_id = D_801F2E90;
    roll    = func_801F2D04() % 6;
    do {
        SYS_ClearFlag(g_SceneEventFlags, *flag_id);
        if (roll & 1) {
            SYS_SetFlag(g_SceneEventFlags, *flag_id);
        }
        flag_id += 1;
        roll >>= 1;
    } while ((s32)flag_id < (s32)(D_801F2E90 + 3));
    func_8019ABB0(0xF);
    SND_PlayCue(0x206U);
    SND_PlayCue(0x202U);
    return 1;
}
