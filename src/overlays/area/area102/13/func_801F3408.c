#include "area102_13.h"

void func_801F3408(void) {
    func_801F36B4(g_SpadWork->unk_09);
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_09 >= 8U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
