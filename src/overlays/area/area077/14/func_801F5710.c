#include "area077_14.h"

MATCH void func_801F5710(void) {
    func_801F529C(3, ((u8)((Actor*)g_Task)->unk_09 >> 1) + 5, 3, 3);
    func_801F529C(6, ((u8)((Actor*)g_Task)->unk_09 >> 1) + 0xB, 6, 9);
    ((Actor*)g_Task)->unk_09 += 1;
    if ((u8)((Actor*)g_Task)->unk_09 >= 6U) {
        ((Actor*)g_Task)->step += 1;
    }
}
