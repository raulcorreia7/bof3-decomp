#include "area108_14.h"

void func_801F55F0(u8 raise) {
    u8  i;
    s16 x;
    s16 y;

    if (raise != 0) {
        for (i = 0; i < 4; i++) {
            x = D_801F63DC[i].x;
            y = D_801F63DC[i].y;
            Area_StoreHeight(x, y, 0xE);
            Area_SetCellCode(x, y, 0x11);
        }
    } else {
        for (i = 0; i < 4; i++) {
            x = D_801F63DC[i].x;
            y = D_801F63DC[i].y;
            Area_StoreHeight(x, y, 0);
            Area_SetCellCode(x, y, 0);
        }
    }
}
