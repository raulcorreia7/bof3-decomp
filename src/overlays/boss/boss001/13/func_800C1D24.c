#include "boss001_13.h"

MATCH void func_800C1D24(void) {
    volatile u16* counter;
    u16           timer;
    s32           value;

    counter  = &D_801463BE;
    timer    = *counter - 1;
    *counter = timer;
    if (timer == 0) {
        value                    = g_Task->pos.y.fixed + COORD_HALF;
        g_Task->pos.y.fixed      = value;
        COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, value);
        Area_SelectSceneRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C21A0;
        g_Task->unk_2A               = 0;
        Actor_SelectScript(0U);
        g_Task->header.step += 1;
    }
    Actor_StepAnimLoop();
}
