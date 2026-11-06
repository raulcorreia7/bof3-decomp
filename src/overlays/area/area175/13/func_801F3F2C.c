#include "area175_13.h"

MATCH s32 func_801F3F2C(s32 entry_x, s32 entry_y) {
    u8* flag;

    if ((u32)((entry_x >> 16) - 65) < 4 && (u32)((entry_y >> 16) - 20) < 4) {
        flag = &D_801455C7;
        if (*flag != 0) {
            *flag = 0;
            SND_PlayCue(EMI_CUE_ID(2, 12));
            Game_RequestAreaChange(D_80145048, D_80145040, D_80145044, FACING_DOWN_RIGHT);
        }
    } else {
        D_801455C7 = 1;
    }
    return 0;
}
