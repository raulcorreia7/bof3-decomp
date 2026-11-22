#include "battle_03.h"

/* Starts the next queued battler: walks the live battler cursors, arms the
 * first one whose row is idle and queues its action step.
 */
/* func_801D1D10 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_NextCommandMember(void) {
    s8*          cursor;
    s8*          slot;
    volatile u8* flag;
    u8*          state;
    u8           mode;
    u8           id;
    u32          index;
    if (EMI_IsReady() != 0) {
        cursor = &g_Battle.command_count;
        if (*cursor == 0)
            g_PadStates[0].held = 0;
        if (*cursor < 3) {
            slot = cursor;
            flag = &g_BattleMessageState;
            for (; *slot < BATTLE_PARTY_CHARACTERS_COUNT; ((u8*)slot)[0] += 1) {
                id    = D_801462F6[*slot];
                index = id & BYTE_MASK;
                if (index != GAME_NONE) {
                    ((u8*)slot)[-0x15] = id;
                    if (!HAS_STATUS(g_Game.members[index], STATUS_CONFUSED) &&
                        !(g_Game.members[index].u.turn.action_flags.volatile_value & (BATTLER_ACTION_DRAGON_FORM_QUEUED | BATTLER_ACTION_CHARGING | BATTLER_ACTION_DRAGON_FORM_BERSERK))) {
                        g_BattleMessageSlot = (u8*)&g_Game.members[index];
                        g_BattleActorTurn   = &g_Game.members[index].u.turn.command;
                        Battle_ShowMessage((s32)&g_Game.members[index]);
                        ((u8*)slot)[-0x22] += 1;
                        *flag       = 1;
                        flag[-0x24] = 1;
                        flag[-0x48] = 1;
                        return;
                    }
                }
            }
        }
        state = &g_Battle.row_cursor;
        FAKE_OPAQUE(state);
        state[0]                 = 0;
        g_Battle.cursor.gene.row = 0;
        mode                     = state[-5];
        D_801463B0               = 0xE;
        state[-4]                = 0;
        state[-5]                = mode + 1;
    }
}
#else
INCLUDE_ASM(Battle_NextCommandMember);
#endif
