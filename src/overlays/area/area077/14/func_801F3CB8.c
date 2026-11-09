#include "area077_14.h"

MATCH void func_801F3CB8(void) {
    WorldPos_Copy(&g_Task->pos, &D_80146954);
    g_Task->vx = 180;
    func_801F41B4();
    g_Task->header.mode++;
}
