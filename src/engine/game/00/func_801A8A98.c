#include "game_00.h"
#include "menu/save_data.h"

MATCH bool func_801A8A98(s32 candidate_x, s32 candidate_y) {
    s32 value;
    u8* buf;

    value = candidate_y;
    if (LOHU(g_GameAreaId) != AREA_ID_ADULT_CAMP) {
        if ((LOBU(g_GameRequestFlags) == 0x40) && (g_GameCellType == 1) && ((Area_CellGetCode((candidate_x >> 0x10), ((value + 0x8000) >> 0x10)) & BYTE_MASK) == 0xA1) && (value > 0x107FFF)) {
            buf = g_SceneEventFlags;
            if (SYS_TestFlag(buf, 119U) != 0) {
                g_SaveData.return_point.pending = 0;
                SYS_ClearFlag(buf, 119U);
                Game_RequestAreaChange(g_SaveData.return_point.area_id, g_SaveData.return_point.x, g_SaveData.return_point.y, FACING_DOWN_RIGHT);
                return 1;
            }
        }
    }
    return 0;
}
