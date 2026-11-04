#include "boss001_13.h"

MATCH void func_800C1A08(void) {
    s32 value;

    if (D_801463BE == 0) {
        value                            = g_SpadWork->coord_y_38.raw + 0x8000;
        g_SpadWork->coord_y_38.raw       = value;
        g_SpadWork->word_3C.half.span_3E = Area_SampleHeight(g_SpadWork->coord_x_34.raw, value);
        Area_FindSceneRecord(0x5F);
        g_BattleCurrentEnemy->script = &D_800C2188;
        g_SpadWork->unk_2A           = 0;
        Actor_SelectScript(1U);
        g_BattleResult |= 4;
        Area_SetCellPalette(0x64, 0x14);
        g_SpadWork->unk_02 += 1;
    }
    func_8014D978();
}
