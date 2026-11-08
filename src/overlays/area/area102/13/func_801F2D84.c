#include "area102_13.h"

MATCH void func_801F2D84(void) {
    func_801F2F44((g_Task)->timer);
    (g_Task)->timer += 1;
    if ((u8)(g_Task)->timer >= 8U) {
        Area_SetCellCode(COORD_INT((g_Task)->pos.x), COORD_INT((g_Task)->pos.y), 0x8A);
        (g_Task)->timer = 0;
        (g_Task)->header.step += 1;
    }
}
