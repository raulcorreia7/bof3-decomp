#include "area148_13.h"

MATCH void func_801F42C0(void) {
    (g_Task)->direction_08     = (g_Task)->param.facing;
    COORD_INT((g_Task)->pos.z) = (u16)COORD_INT((g_Task)->pos.z) + 0xC0;
    Area_SampleForwardHeight();
    (g_Task)->direction_08 = ((g_Task)->direction_08 + 3) & 0x7;
    func_801F45C8();
    (g_Task)->unk_06      = 2;
    (g_Task)->timer       = 80;
    (g_Task)->header.mode = 1;
}
