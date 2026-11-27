#include "battle_15.h"

MATCH void func_800A5E98(void) {
    s32 i;
    s32 entry_index;
    u8  value;
    u8* entry;
    u8* counter;

    g_Battle.gene_count = 0;
    i                   = 0;
    do {
        entry_index = *(s16*)&g_UiPanelTasks[19].u.battle.cursor + FIELD(s16, (&g_UiPanelTasks[19].u.battle.cursor), 0x2u);
        entry       = (u8*)&D_80145518[entry_index];
        value       = entry[i & BYTE_MASK];
        if (value != GAME_NONE) {
            g_Battle.genes[i & BYTE_MASK] = value;
            g_Battle.gene_count           = g_Battle.gene_count + 1;
        }
        i = i + 1;
    } while ((i & BYTE_MASK) < 3U);

    Battle_SetGeneCount();
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
    g_UiPanelTasks[19].state = 2;
    BATTLE_ACTIVE_MEMBER->u.turn.action_flags.volatile_value |= BATTLER_ACTION_ABILITY_ALT_POSE;
    counter  = (u8*)&g_Battle.ui_mode;
    *counter = *counter + 1;
}
