#include "area198_13.h"

MATCH void func_801F2CB8(void) {
    g_Task->unk_09 += 1;
    func_801F2D28(g_Task->unk_09);
    if (g_Task->unk_09 >= 0x80) {
        Actor_Clear();
    }
}
