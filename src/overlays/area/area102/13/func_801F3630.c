#include "area102_13.h"

MATCH void func_801F3630(void) {
    func_801F36B4(((Actor*)g_SpadWork)->unk_09 >> 2);
    ((Actor*)g_SpadWork)->unk_09 -= 1;
    if (((Actor*)g_SpadWork)->unk_09 < 8U) {
        ((Actor*)g_SpadWork)->unk_09   = ((Actor*)g_SpadWork)->unk_0A;
        ((Actor*)g_SpadWork)->state_02 = 1;
    }
}
