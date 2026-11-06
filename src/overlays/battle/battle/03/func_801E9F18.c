#include "battle_03.h"

MATCH void func_801E9F18(void) {
    if ((g_BattleSelectionLatch != 0) && (((Battle_SlotIsBlocked(g_MenuCurrentPanel->unk_0A) & 0xFF) == 0) ||
                                          (func_80097EB8() & 0xFF) || (func_8009AF7C() & 0xFF))) {
        if (D_801EB4D8->command.target == g_MenuCurrentPanel->unk_0A) {
            func_801EA174();
        }
        if ((D_801EB4D8->command.target & 0x80) != 0) {
            func_801EA174();
        }
    }
}
