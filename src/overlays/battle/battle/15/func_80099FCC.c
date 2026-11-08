#include "battle_15.h"

MATCH void func_80099FCC(void) {
    u16 packed;
    u32 flags;

    packed = g_Game.members[g_BattleMessageSlot[5] & BYTE_MASK].u.turn.command.id;
    flags  = Item_GetFlags(packed >> 8, packed & BYTE_MASK);
    if ((flags & 0x20) != 0) {
        g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(3);
        g_Battle.ui_state                 = 1;
    } else {
        if (func_8009AF7C() != 0u) {
            g_BattleActorTurn->command.target = 0u;
        } else {
            g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(0);
        }
        g_Battle.ui_state = 2;
    }
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1;
}
