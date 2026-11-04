#include "area174_13.h"

MATCH void func_801F2D68(void) {
    s32 temp_v0;

    if (!(g_SpadWork->unk_09 & 7)) {
        temp_v0 = func_801F2E88();
        if (temp_v0 != 0) {
            func_801F3378(temp_v0);
        }
    }
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_06 != 0) {
        func_801F2EC4();
    }
    if (D_80147A8C == 0x408000) {
        g_SpadWork->unk_01 += 1;
    }
}
