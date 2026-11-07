#include "area102_13.h"

MATCH void func_801F2E28(void) {
    func_801F2F44(7);
    ((Actor*)g_Task)->timer += 1;
    if ((u8)((Actor*)g_Task)->timer >= 0x1FU) {
        Area_SetCellCode(COORD_INT(((Actor*)g_Task)->pos.x), COORD_INT(((Actor*)g_Task)->pos.y), 0);
        ((Actor*)g_Task)->timer = 0x1F;
        ((Actor*)g_Task)->header.step += 1;
    }
}
