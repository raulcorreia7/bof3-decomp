#include "battle_03.h"

MATCH void func_801D251C(void) {
    u8* counter;
    u8  count;
    u8* otherRecord;
    g_BattleActorTurn->command.type   = BATTLE_COMMAND_DEFEND;
    g_BattleActorTurn->command.target = g_BattleMessageSlot[5];
    otherRecord                       = g_BattleMessageSlot;
    g_BattleActorTurn->damage_flags.value |= COMBATANT_FLAG_DEFENDING;
    *(s8*)(otherRecord + 1) = 2;
    counter                 = (u8*)&g_BattleCommandCount;
    count                   = *counter;
    g_BattleStep            = 1;
    g_BattleSubStep         = 0;
    g_BattleUIStep          = 0;
    *counter                = count + 1u;
}
