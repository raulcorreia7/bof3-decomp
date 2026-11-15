#include "battle_03.h"

/* Starts the next queued battler: walks the live battler cursors, arms the
 * first one whose row is idle and queues its action step.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D1D10(void) {
    s8*          cursor;
    s8*          slot;
    volatile u8* flag;
    u8           id;
    u32          index;
    if (EMI_IsReady() != 0) {
        cursor = &g_Battle.command_count;
        if (*cursor == 0)
            g_InputHeld = 0;
        if (*cursor < 3) {
            slot = cursor;
            for (; *slot < BATTLE_PARTY_CHARACTERS_COUNT; ((u8*)slot)[0] += 1) {
                id    = D_801462F6[*slot];
                index = id & BYTE_MASK;
                if (index != GAME_NONE) {
                    ((u8*)slot)[-0x15] = id;
                    if (!HAS_STATUS(g_Game.members[index], STATUS_CONFUSED) &&
                        !(g_Game.members[index].u.turn.action_flags.volatile_value & (COMBATANT_FLAG_DRAGON_FORM_QUEUED | COMBATANT_FLAG_CHARGING | COMBATANT_FLAG_DRAGON_FORM_BERSERK))) {
                        g_BattleMessageSlot = (u8*)&g_Game.members[index];
                        g_BattleActorTurn   = &g_Game.members[index].u.turn.command;
                        Battle_ShowMessage((s32)&g_Game.members[index]);
                        ((u8*)slot)[-0x22] += 1;
                        flag        = &g_BattleMessageState;
                        *flag       = 1;
                        flag[-0x24] = 1;
                        flag[-0x48] = 1;
                        return;
                    }
                }
            }
        }
        g_Battle.row_cursor         = 0;
        g_Battle.cursor.panel_entry = 0;
        D_801463B0                  = 0xE;
        g_Battle.phase.step         = 0;
        g_Battle.phase.mode += 1;
    }
}
#else
INCLUDE_ASM(func_801D1D10);
#endif
