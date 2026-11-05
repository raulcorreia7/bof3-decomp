#include "area148_13.h"

MATCH void func_801F42C0(void) {
    ((Actor*)g_SpadWork)->direction_08   = ((Actor*)g_SpadWork)->unk_0B;
    ((Actor*)g_SpadWork)->z.part.integer = (u16)((Actor*)g_SpadWork)->z.part.integer + 0xC0;
    func_801F4544();
    ((Actor*)g_SpadWork)->direction_08 = (((Actor*)g_SpadWork)->direction_08 + 3) & 7;
    func_801F45C8();
    ((Actor*)g_SpadWork)->unk_06 = 2;
    ((Actor*)g_SpadWork)->unk_09 = 0x50;
    ((Actor*)g_SpadWork)->unk_01 = 1;
}
