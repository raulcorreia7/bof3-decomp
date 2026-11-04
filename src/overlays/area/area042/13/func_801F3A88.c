#include "area042_13.h"

MATCH void func_801F3A88(void) {
    func_801F3D18(D_801F534C[g_SpadWork->unk_09 >> 1]);
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_09 >= 5U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
