#include "boss025_13.h"

MATCH void func_800C2128(void) {
    if (!(g_BattleBossFlags & 0x8)) {
        g_BattleTargetSelector = 3;
    } else {
        g_BattleActionType = BATTLE_ACTION_NONE;
    }
}
