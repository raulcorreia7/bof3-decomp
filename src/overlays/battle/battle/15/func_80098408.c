#include "battle_15.h"

MATCH void func_80098408(void) {
    BattleTurn* actor_turn;
    u8*         battle_selection_state;
    u8          selection_root_state;

    actor_turn               = g_BattleActorTurn;
    battle_selection_state   = (u8*)(u8*)(PARTY_STATE_PTR);
    actor_turn->command.type = BATTLE_COMMAND_ITEM;
    func_8009AF84();
    selection_root_state            = battle_selection_state[0x62E3u];
    battle_selection_state[0x62E4u] = 0u;
    battle_selection_state[0x62E3u] = selection_root_state + 1u;
}
