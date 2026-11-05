#include "battle_15.h"

MATCH void func_800A5164(void) {
    s32 i;
    s32 row;
    u8  value;
    u8* slot;
    u8* counter;

    g_BattleGeneCount[0] = 0;
    i                    = 0;
    do {
        row   = MEM(s16, (u32)&g_BattleTargetCursorCol) + FIELD(s16, (&g_BattleTargetCursorCol), 0x2u);
        slot  = (u8*)&g_BattleTargetRows[row];
        value = slot[i & BYTE_MASK];
        if (value != GAME_NONE) {
            g_BattleGenes[i & BYTE_MASK] = value;
            g_BattleGeneCount[0]         = g_BattleGeneCount[0] + 1;
        }
        i = i + 1;
    } while ((u32)(i & BYTE_MASK) < 3U);

    func_800A82F8();
    g_BattlePanelMode = 2;
    BATTLE_ACTIVE_ROW->action_flags.volatile_value |= 4;
    counter  = (u8*)&g_BattleUiState;
    *counter = *counter + 1;
}
