#include "area102_13.h"

MATCH void func_801F2D84(void) {
    func_801F2F44(((Actor*)g_Task)->unk_09);
    ((Actor*)g_Task)->unk_09 += 1;
    if ((u8)((Actor*)g_Task)->unk_09 >= 8U) {
        func_801A4BC0(((Actor*)g_Task)->x.part.integer, ((Actor*)g_Task)->y.part.integer, 0x8A);
        ((Actor*)g_Task)->unk_09 = 0;
        ((Actor*)g_Task)->step += 1;
    }
}
