#include "battle_15.h"

MATCH void func_80098408(void) {
    BattleTurn* active_selection_slot;
    u8*         battle_selection_state;
    u8          selection_root_state;

    active_selection_slot               = D_801EB4D8;
    battle_selection_state              = (u8*)(u8*)(EFFECT_BANK_80140000);
    active_selection_slot->command.type = 5u;
    func_8009AF84();
    selection_root_state            = battle_selection_state[0x62E3u];
    battle_selection_state[0x62E4u] = 0u;
    battle_selection_state[0x62E3u] = selection_root_state + 1u;
}
