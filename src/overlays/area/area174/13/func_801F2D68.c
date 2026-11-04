#include "area174_13.h"

MATCH void func_801F2D68(void) {
    s32 result;

    if (!(g_SpadWork->unk_09 & 7)) {
        result = func_801F2E88();
        if (result != 0) {
            func_801F3378(result);
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
