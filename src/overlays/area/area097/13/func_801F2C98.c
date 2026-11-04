#include "area097_13.h"

MATCH s32 func_801F2C98(s32 x, s32 y) {
    u8 facing = D_80145E98;

    if (y <= 0x3A0000 && (u32)((x >> 16) - 0x30) < 3U) {
        if ((facing < 2U || facing == 2) && Party_HasVitalItem(5) == 0) {
            D_80146867 = 1;
            D_801448EB = 0xD;
            D_801448EC = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
