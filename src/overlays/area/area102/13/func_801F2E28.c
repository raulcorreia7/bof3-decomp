#include "area102_13.h"

MATCH void func_801F2E28(void) {
    func_801F2F44(7);
    (g_Task)->timer += 1;
    if ((u8)(g_Task)->timer >= 0x1FU) {
        Area_SetCellCode(COORD_INT((g_Task)->pos.x), COORD_INT((g_Task)->pos.y), 0);
        (g_Task)->timer = 0x1F;
        (g_Task)->header.step += 1;
    }
}
