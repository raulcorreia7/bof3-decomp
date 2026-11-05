#include "boss001_13.h"

MATCH void func_800C1D24(void) {
    volatile u16* counter;
    u16           timer;
    s32           value;

    counter  = &D_801463BE;
    timer    = *counter - 1;
    *counter = timer;
    if (timer == 0) {
        value                        = g_Task->coord_y_38.raw + 0x8000;
        g_Task->coord_y_38.raw       = value;
        g_Task->word_3C.half.span_3E = Area_SampleHeight(g_Task->coord_x_34.raw, value);
        Area_FindSceneRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C21A0;
        g_Task->unk_2A               = 0;
        Actor_SelectScript(0U);
        g_Task->step += 1;
    }
    func_8014D978();
}
