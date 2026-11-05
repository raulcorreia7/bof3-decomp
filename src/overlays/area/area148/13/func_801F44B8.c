#include "area148_13.h"

MATCH void func_801F44B8(void) {
    func_801F4798(&((Actor*)g_SpadWork)->x, &((Actor*)g_SpadWork)->unk_18);
    func_801F4614();
    ((Actor*)g_SpadWork)->unk_0A -= 1;
    if (((Actor*)g_SpadWork)->unk_0A == 0) {
        ((Actor*)g_SpadWork)->unk_09 += 1;
        ((Actor*)g_SpadWork)->unk_01 = 1;
    }
}
