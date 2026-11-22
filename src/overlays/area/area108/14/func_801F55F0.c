#include "area108_14.h"

MATCH void func_801F55F0(u8 raise) {
    u8  i;
    s16 x;
    s16 y;

    if (raise != 0) {
        for (i = 0; i < 4; i++) {
            x = D_801F63DC[i].vx;
            y = D_801F63DC[i].vy;
            Area_HeightSet(x, y, 0xE);
            Area_CellSetCode(x, y, 0x11);
        }
    } else {
        for (i = 0; i < 4; i++) {
            x = D_801F63DC[i].vx;
            y = D_801F63DC[i].vy;
            Area_HeightSet(x, y, 0);
            Area_CellSetCode(x, y, 0);
        }
    }
}
