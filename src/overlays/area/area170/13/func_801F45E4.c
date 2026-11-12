#include "area170_13.h"

MATCH void func_801F45E4(void) {
    u16 value;

    value            = g_Task->screen_y + 0x20;
    g_Task->screen_y = value;
    if ((s16)value >= 0x100) {
        Area_SetCellPalette(9, 15);
        Actor_Clear();
    }
    func_801F4640(0);
}
