#include "area048_13.h"

MATCH void func_801F3F98(void) {
    if (((((Actor*)g_SpadWork)->x.part.integer == 0) && (SYS_TestFlag(g_SceneEventFlags, 0xD) == 0)) ||
        ((((Actor*)g_SpadWork)->x.part.integer != 0) && (D_8014686B == 0))) {
        ((Actor*)g_SpadWork)->unk_09 = 0;
        ((Actor*)g_SpadWork)->state_02 += 1;
    }
    ((Actor*)g_SpadWork)->unk_09 += 1;
    if ((u8)((Actor*)g_SpadWork)->unk_09 >= 0x41U) {
        ((Actor*)g_SpadWork)->unk_09 = 0;
        if (rand() & 1) {
            ((Actor*)g_SpadWork)->state_02 = 5;
        }
    }
    func_801F4258(((Actor*)g_SpadWork)->x.part.integer);
}
