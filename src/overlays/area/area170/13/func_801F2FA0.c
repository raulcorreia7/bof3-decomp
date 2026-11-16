#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FA0(s16 x, s16 y, s8* glyphs, u8 phase) {
    s16 left = x;
    s16 top  = y;
    s16 right;
    s16 bottom;
    u8  i;
    u8  col;

    func_801F3838(2);
    right  = x + 0x5A;
    bottom = y + 0x46;
    func_801F3594(x, y, right, y, x, bottom, right, bottom, 0x40, 0x40, 0x40, 1);
    func_801F3838(1);
    for (i = 0; i < 10; i++) {
        func_801F3774(left + i * 10, top, left + i * 10, top + 0x45, 0x96, 0x96, 0x96, 0);
    }
    for (i = 0; i < 8; i++) {
        func_801F3774(left, top + i * 10, left + 0x59, top + i * 10, 0x96, 0x96, 0x96, 0);
    }
    for (i = 0; i < 9; i++) {
        for (col = 0; col < 7; col++) {
            func_801F388C(left + i * 10, top + col * 10, glyphs[col * 9 + phase]);
        }
        phase++;
        if (phase >= 9) {
            phase = 0;
        }
    }
}
#else
INCLUDE_ASM(func_801F2FA0);
#endif
