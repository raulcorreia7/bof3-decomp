#include "area120_13.h"

MATCH void func_801F3D14(void) {
    u8 step;

    g_SpadWork->unk_09 += 2;
    step = g_SpadWork->unk_09;
    func_801F3F5C(0x80 - (step * 2), 0x40 - step, 1, 0);
    if (g_SpadWork->unk_09 >= 0x40U) {
        func_80196070();
    }
}
