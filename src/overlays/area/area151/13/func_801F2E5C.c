#include "area151_13.h"

MATCH void func_801F2E5C(void) {
    s32 x;
    s32 y;
    s32 scaled;
    u8* scratch;

    scaled = g_BattlePartyBattlers[0].unk_0C * g_BattlePartyBattlers[0].unk_09;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC4[1] + g_BattlePartyBattlers[0].unk_10 * g_BattlePartyBattlers[0].unk_09) >> 16;

    scratch                 = (u8*)g_Task;
    *(s32*)(scratch + 0x0C) = x;
    *(s32*)(scratch + 0x10) = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {
        TASK_BYTES[0x0B] = 1;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {
        TASK_BYTES[0x0B] = 2;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {
        TASK_BYTES[0x0B] = 3;
    } else if (g_AreaWalkFlags & AREA_WALK_TRANSITION) {
        TASK_BYTES[0x0B] = 4;
    } else {
        TASK_BYTES[0x0B] = 0;
    }

    D_801F542C[TASK_BYTES[1]]();
}
