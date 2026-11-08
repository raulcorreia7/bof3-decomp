#include "battle_03.h"

MATCH void func_801E9F18(void) {
    if ((g_Battle.selection_latch != 0) && (((Battle_SlotIsBlocked(g_MenuCurrentPanel->unk_0A) & BYTE_MASK) == 0) ||
                                            (func_80097EB8() & BYTE_MASK) || (func_8009AF7C() & BYTE_MASK))) {
        if (g_BattleActorTurn->command.target == g_MenuCurrentPanel->unk_0A) {
            func_801EA174();
        }
        if ((g_BattleActorTurn->command.target & BATTLE_TARGET_PARTY_SIDE) != 0) {
            func_801EA174();
        }
    }
}
