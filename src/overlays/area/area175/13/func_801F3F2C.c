#include "area175_13.h"
#include "menu/save_data.h"

MATCH s32 func_801F3F2C(s32 entry_x, s32 entry_y) {
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
