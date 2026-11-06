#include "area121_14.h"

MATCH void func_801F2F04(void) {
    s32    x;
    s32    y;
    s32    scaled;
    Actor* work;

    scaled = g_BattlePartyBattlers[0].unk_0C * g_BattlePartyBattlers[0].unk_09;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC8 + g_BattlePartyBattlers[0].unk_10 * g_BattlePartyBattlers[0].unk_09) >> 16;

    work     = g_Task;
    work->vx = x;
    work->vy = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {
        g_Task->unk_0B = 1;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {
        g_Task->unk_0B = 2;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {
        g_Task->unk_0B = 3;
    } else if (g_AreaWalkFlags & AREA_WALK_TRANSITION) {
        g_Task->unk_0B = 4;
    } else {
        g_Task->unk_0B = 0;
    }

    D_801F67C4[g_Task->mode]();
}
