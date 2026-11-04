#include "boss001_13.h"

MATCH void func_800C1A08(void) {
    s32 temp_a1;

    if (D_801463BE == 0) {
        temp_a1                                     = ((PartyBattler*)g_SpadWork)->coord_y_38.raw + 0x8000;
        ((PartyBattler*)g_SpadWork)->coord_y_38.raw = temp_a1;
        ((PartyBattler*)g_SpadWork)->word_3C.half.span_3E =
            Area_SampleHeight(((PartyBattler*)g_SpadWork)->coord_x_34.raw, temp_a1);
        Area_FindSceneRecord(0x5F);
        g_BattleCurrentEnemy->script        = &D_800C2188;
        ((PartyBattler*)g_SpadWork)->unk_2A = 0;
        Actor_SelectScript(1U);
        g_BattleResult |= 4;
        Area_SetCellPalette(0x64, 0x14);
        ((PartyBattler*)g_SpadWork)->unk_02 += 1;
    }
    func_8014D978();
}
