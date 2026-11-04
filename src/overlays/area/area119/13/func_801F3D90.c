#include "area119_13.h"

MATCH void func_801F3D90(void) {
    func_801F3F04(g_SpadWork->unk_09);
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_09 >= 8U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
