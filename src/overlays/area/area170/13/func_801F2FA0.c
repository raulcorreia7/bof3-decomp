#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FA0(s16 x, s16 y, s8* glyphs, u8 phase) {
    s16 px;
    s16 py;
    u8  i;
    u8  j;

    func_801F3838(2);
    func_801F3594(x, y, x + 0x5A, y, x, y + 0x46, x + 0x5A, y + 0x46, 0x40, 0x40, 0x40, 1);
    func_801F3838(1);
    for (i = 0; i < 10; i++) {
        px = x + i * 10;
        func_801F3774(px, y, px, y + 0x45, 0x96, 0x96, 0x96, 0);
    }
    for (i = 0; i < 8; i++) {
        py = y + i * 10;
        func_801F3774(x, py, x + 0x59, py, 0x96, 0x96, 0x96, 0);
    }
    for (i = 0; i < 9; i++) {
        px = x + i * 10;
        for (j = 0; j < 7; j++) {
            func_801F388C(px, (s16)(y + j * 10), glyphs[j * 9 + phase]);
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
