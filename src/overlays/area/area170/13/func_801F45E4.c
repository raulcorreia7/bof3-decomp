#include "area170_13.h"

MATCH void func_801F45E4(void) {
    u16 value;

    value              = g_SpadWork->unk_30 + 0x20;
    g_SpadWork->unk_30 = value;
    if ((s16)value >= 0x100) {
        Area_SetCellPalette(9, 0xF);
        Actor_Clear();
    }
    func_801F4640(0);
}
