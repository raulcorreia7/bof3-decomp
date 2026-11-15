#include "battle_15.h"

MATCH void func_800A5E98(void) {
    s32 i;
    s32 row;
    u8  value;
    u8* slot;
    u8* counter;

    g_Battle.gene_count = 0;
    i                   = 0;
    do {
        row   = *(s16*)&D_801485EC + FIELD(s16, (&D_801485EC), 0x2u);
        slot  = (u8*)&D_80145518[row];
        value = slot[i & BYTE_MASK];
        if (value != GAME_NONE) {
            g_Battle.genes[i & BYTE_MASK] = value;
            g_Battle.gene_count           = g_Battle.gene_count + 1;
        }
        i = i + 1;
    } while ((i & BYTE_MASK) < 3U);

    Battle_SetGeneCount();
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
    D_801485DF = 2;
    BATTLE_ACTIVE_ROW->u.turn.action_flags.volatile_value |= COMBATANT_FLAG_ABILITY_ALT_POSE;
    counter  = (u8*)&g_Battle.ui_state;
    *counter = *counter + 1;
}
