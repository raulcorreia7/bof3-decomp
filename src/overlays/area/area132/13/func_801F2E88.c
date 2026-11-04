#include "area132_13.h"

MATCH void func_801F2E88(void) {
    s32 result;
    u8  count;

    if (!(g_SpadWork->unk_09 & 3)) {
        result = func_801F3800();
        if (result != 0) {
            func_801F37A4(result);
        }
    }
    func_801F38B0();
    count              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = count;
    if (count == 0) {
        g_SpadWork->state_02 += 1;
    }
}
