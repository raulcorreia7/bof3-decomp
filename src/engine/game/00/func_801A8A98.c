#include "game_00.h"

MATCH s32 func_801A8A98(s32 candidate_x, s32 candidate_y) {
    s32 value;
    u8* buf;

    value = candidate_y;
    if (LOHU(g_GameAreaId) != 0xBB) {
        if ((LOBU(g_GameRequestFlags) == 0x40) && (D_80143F03 == 1) &&
            ((Area_GetCellCode((s16)(candidate_x >> 0x10), (s16)((s32)(value + 0x8000) >> 0x10)) & BYTE_MASK) ==
             0xA1) &&
            (value > 0x107FFF)) {
            buf = (u8*)&g_SceneEventFlags;
            if (SYS_TestFlag(buf, 0x77U) != 0) {
                D_8014504A = 0;
                SYS_ClearFlag(buf, 0x77U);
                Game_RequestAreaChange(D_80145048, (u32)D_80145040, (u32)D_80145044, 4U);
                return 1;
            }
        }
    }
    return 0;
}
