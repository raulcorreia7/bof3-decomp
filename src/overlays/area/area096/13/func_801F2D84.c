#include "area096_13.h"

MATCH void func_801F2D84(void) {
    u8* width;

    func_801F2ECC(TASK(Actor)->pos.z.fixed, 0x80);
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer == 0) {
        width                               = MEM_PTR(u8, 0x80104000u);
        g_AreaCellCodes[*width * 60 + 0x45] = 0;
        g_AreaCellCodes[*width * 60 + 0x46] = 0;
        TASK(Actor)->header.step += 1;
    }
}
