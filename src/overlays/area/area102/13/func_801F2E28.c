#include "area102_13.h"

MATCH void func_801F2E28(void) {
    func_801F2F44(7);
    ((Actor*)g_SpadWork)->unk_09 += 1;
    if ((u8)((Actor*)g_SpadWork)->unk_09 >= 0x1FU) {
        func_801A4BC0(((Actor*)g_SpadWork)->x.part.integer, ((Actor*)g_SpadWork)->y.part.integer, 0);
        ((Actor*)g_SpadWork)->unk_09 = 0x1F;
        ((Actor*)g_SpadWork)->state_02 += 1;
    }
}
