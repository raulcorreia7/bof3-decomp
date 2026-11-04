#include "boss001_13.h"

MATCH void func_800C1D24(void) {
    volatile u16* counter;
    u16           timer;
    s32           value;

    counter  = &D_801463BE;
    timer    = *counter - 1;
    *counter = timer;
    if (timer == 0) {
        value                            = g_SpadWork->coord_y_38.raw + 0x8000;
        g_SpadWork->coord_y_38.raw       = value;
        g_SpadWork->word_3C.half.span_3E = Area_SampleHeight(g_SpadWork->coord_x_34.raw, value);
        Area_FindSceneRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C21A0;
        g_SpadWork->unk_2A           = 0;
        Actor_SelectScript(0U);
        g_SpadWork->unk_02 += 1;
    }
    func_8014D978();
}
