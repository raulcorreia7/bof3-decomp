#include "battle_03.h"

/* Starts the next queued battler: walks the command order, arms the first row
 * that is free of status and of a queued action, and queues its message. */
/* func_801D1D10 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_NextCommandMember(void) {
    s8*          cursor;
    s8*          slot;
    volatile u8* flag;
    u8*          state;
    u8           id;
    u8           index;
    u8           mode;

    if (EMI_IsReady() == 0) {
        return;
    }
    cursor = (s8*)&g_Battle.command_count;
    if (*cursor == 0) {
        g_PadStates[0].held = 0;
    }
    if (*cursor < BATTLE_PARTY_CHARACTERS_COUNT) {
        slot = cursor;
        /* The three UI bytes the armed message slot gates on. */
        flag = &g_BattleMessageState;
        for (; *slot < BATTLE_PARTY_CHARACTERS_COUNT; ((u8*)slot)[0] += 1) {
            id    = D_801462F6[*slot];
            index = id & BYTE_MASK;
            if (index == GAME_NONE) {
                continue;
            }
            ((u8*)slot)[-0x15] = id; /* g_Battle.unk_0E */
            if (HAS_STATUS(g_Game.members[index], STATUS_CONFUSED)) {
                continue;
            }
            if ((g_Game.members[index].u.turn.action_flags.volatile_value & (BATTLER_ACTION_DRAGON_FORM_QUEUED | BATTLER_ACTION_CHARGING | BATTLER_ACTION_DRAGON_FORM_BERSERK)) != 0) {
                continue;
            }
            g_BattleMessageSlot = (u8*)&g_Game.members[index];
            g_BattleActorTurn   = &g_Game.members[index].u.turn;
            Battle_ShowMessage((s32)&g_Game.members[index]);
            ((u8*)slot)[-0x22] += 1; /* g_Battle.phase.step */
            flag[0]     = 1;
            flag[-0x24] = 1;
            flag[-0x48] = 1;
            return;
        }
    }
    /* row_cursor, then the phase mode and step bytes before it. */
    state                       = &g_Battle.row_cursor;
    state[0]                    = 0;
    g_Battle.cursor.panel_entry = 0;
    mode                        = state[-5];
    D_801463B0                  = 0x0E;
    state[-4]                   = 0;
    state[-5]                   = mode + 1;
}
#else
INCLUDE_ASM(Battle_NextCommandMember);
#endif
