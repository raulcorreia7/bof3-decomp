#include "area095_13.h"

MATCH void func_801F2DF4(void) {
    u8* width;

    func_801F2F3C(g_Task->pos.z.fixed, 0x80);
    g_Task->timer -= 1;
    if (g_Task->timer == 0) {
        width                               = MEM_PTR(u8, 0x80104000u);
        g_AreaCellCodes[*width * 60 + 0x45] = 0;
        g_AreaCellCodes[*width * 60 + 0x46] = 0;
        g_Task->header.step += 1;
    }
}
