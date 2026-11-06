#include "battle_15.h"

MATCH void func_800AB570(s32 battler_index) {
    u8 index;
    u8 value;
    u8 result;

    index = battler_index & BYTE_MASK;
    value = g_BattlePartyBattlers[index].counter_136;
    if ((s8)g_BattlePartyBattlers[index].counter_136 >= 6) {
        value = 5;
    }
    if ((rand() % 20) < (s8)value && g_BattleLivingPartyCount != 1) {
        result = func_800AB68C(index);
    } else {
        result = Battle_FindSelectableSlotForward(RANDOM_MASK(7) + 3);
    }
    g_BattleTargetSelector                         = result;
    g_BattlePartyBattlers[index].turn.command.type = BATTLE_COMMAND_ATTACK;
    g_BattleActionType                             = BATTLE_ACTION_ATTACK;
}
