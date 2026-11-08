#include "battle_15.h"

MATCH void func_800AB570(s32 battler_index) {
    u8 index;
    u8 value;
    u8 result;

    index = battler_index & BYTE_MASK;
    value = g_Game.members[index].counter_136;
    if ((s8)g_Game.members[index].counter_136 >= 6) {
        value = 5;
    }
    if ((RANDOM_MOD(20)) < (s8)value && g_Battle.living_party_count != 1) {
        result = func_800AB68C(index);
    } else {
        result = Battle_FindSelectableSlotForward(RANDOM_MASK(7) + 3);
    }
    g_Battle.target_selector                  = result;
    g_Game.members[index].u.turn.command.type = BATTLE_COMMAND_ATTACK;
    g_Battle.action_type                      = BATTLE_ACTION_ATTACK;
}
