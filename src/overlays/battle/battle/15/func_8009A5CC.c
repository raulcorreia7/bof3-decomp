#include "battle_15.h"

MATCH void func_8009A5CC(void) {
    u16 packed;
    u32 flags;

    packed = g_Game.members[g_BattleMessageSlot[5] & BYTE_MASK].u.turn.command.id;
    flags  = Item_GetFlags(packed >> 8, packed & BYTE_MASK);
    if ((flags & 0x20) != 0) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_BattleUIState        = 1;
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
