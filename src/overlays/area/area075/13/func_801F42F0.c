#include "area075_13.h"

MATCH void func_801F42F0(void) {
    u16* timer;

    switch (D_801F58C3) {
        case 2:
            func_801F45A8();
        case 1:
            func_801F46D4();
            break;

        case 0:
            func_801F45A8();
        default:
            func_801F47BC();
            break;
    }

    timer = &D_801F58C4;
    *timer -= 1;
    if (*timer == 0) {
        if (!(D_801F58C6 & 0x8)) {
            D_801F58C0 = 1;
        } else {
            *timer = 10000;
        }
    }

    if (!(D_801F58C6 & 0x8)) {
        if (D_801F58C7 >= 4 || D_801F58C8 >= 0x1F || abs(D_801F58CA - D_801F58CC) >= 0xC9) {
            D_801F58C0 = 3;
        }
    }
}
