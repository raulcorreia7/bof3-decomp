#include "game_00.h"

MATCH bool func_801A8A98(s32 candidate_x, s32 candidate_y) {
    s32 value;
    u8* buf;

    value = candidate_y;
    if (LOHU(g_GameAreaId) != AREA_ID_ADULT_CAMP) {
        if ((LOBU(g_GameRequestFlags) == 0x40) && (D_80143F03 == 1) && ((Area_GetCellCode((candidate_x >> 0x10), ((value + 0x8000) >> 0x10)) & BYTE_MASK) == 0xA1) && (value > 0x107FFF)) {
            buf = (u8*)&g_SceneEventFlags;
            if (SYS_TestFlag(buf, 119U) != 0) {
                D_8014504A = 0;
                SYS_ClearFlag(buf, 119U);
                Game_RequestAreaChange(D_80145048, D_80145040, D_80145044, FACING_DOWN_RIGHT);
                return 1;
            }
        }
    }
    return 0;
}
