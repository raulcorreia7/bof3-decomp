#include "area082_13.h"

MATCH void func_801F4F88(void) {
    *(s16*)0x1F800014 = -0x2E40;
    *(s16*)0x1F800016 = -0x3240;
    *(s16*)0x1F800018 = -0x3E0;
    *(s16*)0x1F80001C = 0;
    *(s16*)0x1F80001E = 0;
    *(s16*)0x1F800020 = g_FrameCount << 5;
    func_801F46C8(g_SpadWork->unk_09 * 4, 0x1F, 0, 0x18);
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 8U) {
        g_SpadWork->state_02 += 1;
    }
}
