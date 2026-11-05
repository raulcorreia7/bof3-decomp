#include "area148_13.h"

MATCH void func_801F42C0(void) {
    ((Actor*)g_Task)->direction_08   = ((Actor*)g_Task)->unk_0B;
    COORD_INT(((Actor*)g_Task)->z) = (u16)COORD_INT(((Actor*)g_Task)->z) + 0xC0;
    func_801F4544();
    ((Actor*)g_Task)->direction_08 = (((Actor*)g_Task)->direction_08 + 3) & 7;
    func_801F45C8();
    ((Actor*)g_Task)->unk_06 = 2;
    ((Actor*)g_Task)->unk_09 = 0x50;
    ((Actor*)g_Task)->mode   = 1;
}
