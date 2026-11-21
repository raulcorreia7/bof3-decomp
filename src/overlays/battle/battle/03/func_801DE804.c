#include "battle_03.h"

MATCH void func_801DE804(void) {
    u8  index;
    u32 offset;

    for (index = 0u; index < 8u; index++) {
        offset                                         = index * 12u;
        ((volatile u8*)g_BattleEventSlots)[offset]     = 0u;
        ((volatile u8*)g_BattleEventSlots + 1)[offset] = 0u;
        ((s8*)&g_BattleEventSlots[0].value)[offset]    = 0;
    }
}
