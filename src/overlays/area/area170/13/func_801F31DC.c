#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F31DC(s16 x, s16 y) {
    u8  sample;
    s32 sample_x;

    func_801F3838(0);
    func_801F3594(x, y + 5, x + 5, y, x, y + 0x55, x + 5, y + 0x5A, 0, 0x80, 0, 1);
    func_801F3594(x + 5, y, x + 0x131, y, x + 5, y + 0x5A, x + 0x131, y + 0x5A, 0, 0x80, 0, 1);
    func_801F3594(x + 0x131, y, x + 0x136, y + 5, x + 0x131, y + 0x5A, x + 0x136, y + 0x55, 0, 0x80, 0, 1);
    if (((g_FrameCount >> 4) & 1) != 0) {
        sample   = TASK(Actor)->unk_06;
        sample_x = (x - 1) + sample * 100;
        func_801F3698(sample_x + 7, y + 0x29, sample_x + 3, y + 0x2D, sample_x + 7, y + 0x31, 0xC8, 0xC8, 0xC8, 0);
        func_801F3698(sample_x + 0x68, y + 0x29, sample_x + 0x6C, y + 0x2D, sample_x + 0x68, y + 0x31, 0xC8, 0xC8, 0xC8, 0);
        sample_x += 0xA;
        func_801F3774(sample_x, y + 5, sample_x + 0x5A, y + 5, 0xC8, 0xC8, 0xC8, 0);
        func_801F3774(sample_x, y + 5, sample_x, y + 0x50, 0xC8, 0xC8, 0xC8, 0);
        func_801F3774(sample_x, y + 0x50, sample_x + 0x5A, y + 0x50, 0xC8, 0xC8, 0xC8, 0);
        func_801F3774(sample_x + 0x5A, y + 5, sample_x + 0x5A, y + 0x50, 0xC8, 0xC8, 0xC8, 0);
    }
}
#else
INCLUDE_ASM(func_801F31DC);
#endif
