#include "battle_15.h"

MATCH void func_800A5E98(void) {
    s32 i;
    s32 row;
    u8  value;
    u8* slot;
    u8* counter;

    g_BattleGeneCount[0] = 0;
    i                    = 0;
    do {
        row   = *(s16*)&D_801485EC + FIELD(s16, (&D_801485EC), 0x2u);
        slot  = (u8*)&D_80145518[row];
        value = slot[i & BYTE_MASK];
        if (value != GAME_NONE) {
            g_BattleGenes[i & BYTE_MASK] = value;
            g_BattleGeneCount[0]         = g_BattleGeneCount[0] + 1;
        }
        i = i + 1;
    } while ((i & BYTE_MASK) < 3U);

    func_800A82F8();
    SND_PlayCue(EMI_CUE_ID(1, 4));
    D_801485DF = 2;
    BATTLE_ACTIVE_ROW->action_flags.volatile_value |= 4;
    counter  = (u8*)&g_BattleUIState;
    *counter = *counter + 1;
}
