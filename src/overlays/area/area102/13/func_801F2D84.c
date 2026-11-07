#include "area102_13.h"

MATCH void func_801F2D84(void) {
    func_801F2F44(((Actor*)g_Task)->timer);
    ((Actor*)g_Task)->timer += 1;
    if ((u8)((Actor*)g_Task)->timer >= 8U) {
        Area_SetCellCode(COORD_INT(((Actor*)g_Task)->pos.x), COORD_INT(((Actor*)g_Task)->pos.y), 0x8A);
        ((Actor*)g_Task)->timer = 0;
        ((Actor*)g_Task)->header.step += 1;
    }
}
