#include "battle_03.h"

MATCH void func_801D251C(void) {
    u8* counter;
    u8  count;
    u8* otherRecord;
    D_801EB4D8->command.type   = BATTLE_COMMAND_DEFEND;
    D_801EB4D8->command.target = g_BattleMessageSlot[5];
    otherRecord                = g_BattleMessageSlot;
    D_801EB4D8->damage_flags.value |= 2u;
    *(s8*)(otherRecord + 1) = 2;
    counter                 = (u8*)&g_BattleCommandCount;
    count                   = *counter;
    g_BattleStep            = 1;
    g_BattleSubStep         = 0;
    g_BattleUIStep          = 0;
    *counter                = count + 1u;
}
