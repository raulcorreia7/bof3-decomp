#include "area148_13.h"

MATCH void func_801F42C0(void) {
    ((Actor*)g_Task)->direction_08     = ((Actor*)g_Task)->param.facing;
    COORD_INT(((Actor*)g_Task)->pos.z) = (u16)COORD_INT(((Actor*)g_Task)->pos.z) + 0xC0;
    func_801F4544();
    ((Actor*)g_Task)->direction_08 = (((Actor*)g_Task)->direction_08 + 3) & 7;
    func_801F45C8();
    ((Actor*)g_Task)->unk_06      = 2;
    ((Actor*)g_Task)->timer       = 0x50;
    ((Actor*)g_Task)->header.mode = 1;
}
