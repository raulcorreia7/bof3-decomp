#include "battle_15.h"

MATCH void func_80097FE8(void) {
    /* FAKE: retail keeps the work base live in a0 for the ending 0x6C store. */
    FAKE_REG(volatile u8*, work, "a0");
    volatile u8*         message_slot;
    volatile BattleTurn* actor_turn;
    u32                  active_selection_flags;
    u8                   entry_index;
    u8                   eight;

    work                                = g_BattleChoicePanel;
    work[0]                             = 1u;
    eight                               = 8u;
    g_BattleChoicePanel[1]              = eight;
    g_BattleChoicePanel[2]              = 2u;
    g_BattleChoicePanel[3]              = 2u;
    g_BattleChoicePanel[0xB]            = 2u;
    message_slot                        = (u8*)(BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    actor_turn                          = g_BattleActorTurn;
    entry_index                         = message_slot[5];
    g_BattleChoicePanel[0xD]            = 0xFFu;
    g_BattleChoicePanel[8]              = 2u;
    g_BattleChoicePanel[9]              = 0u;
    g_BattleChoicePanel[0xA]            = entry_index;
    active_selection_flags              = actor_turn->action_flags.value;
    VOL(u16, g_BattleChoicePanel[4])    = 0x140u;
    VOL(u16, g_BattleChoicePanel[6])    = 0x3Fu;
    VOL(u16, g_BattleChoicePanel[0x14]) = (active_selection_flags & 0x2u);
    D_80148656                          = message_slot[5];
    /* FAKE: alias keeps the work base in the register. */
    FAKE_OPAQUE(work);
    work[0x6C] = 0u;
    D_801485DD = eight;
    D_801485DE = 0u;
}
