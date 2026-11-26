#include "menu/save_data.h"

MATCH u16 func_801F33E4(s32 entry_x, s32 entry_y) {
    u8* flag;

    if ((u32)((entry_x >> 16) - 65) < 4 && (u32)((entry_y >> 16) - 20) < 4) {
        flag = &D_801455C7;
        if (*flag != 0) {
            *flag = 0;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
            Game_RequestAreaChange(g_SaveData.return_point.area_id, g_SaveData.return_point.x, g_SaveData.return_point.y, FACING_DOWN_RIGHT);
        }
    } else {
        D_801455C7 = 1;
    }
    return 0;
}
