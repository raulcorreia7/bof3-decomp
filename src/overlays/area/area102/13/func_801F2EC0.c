#include "area102_13.h"

MATCH void func_801F2EC0(void) {
    func_801F2F44(((Actor*)g_Task)->unk_09 >> 2);
    ((Actor*)g_Task)->unk_09 -= 1;
    if (((Actor*)g_Task)->unk_09 < 8U) {
        ((Actor*)g_Task)->unk_09 = ((Actor*)g_Task)->unk_0A;
        ((Actor*)g_Task)->step   = 1;
    }
}
