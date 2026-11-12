#include "boss001_13.h"

MATCH void func_800C1A08(void) {
    s32 value;

    if (D_801463BE == 0) {
        value                    = g_Task->pos.y.fixed + COORD_HALF;
        g_Task->pos.y.fixed      = value;
        COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, value);
        Area_FindSceneRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C2188;
        g_Task->unk_2A               = 0;
        Actor_SelectScript(1U);
        g_BattleResult |= 4;
        Area_SetCellPalette(100, 20);
        g_Task->header.step += 1;
    }
    Actor_StepAnimLoop();
}
