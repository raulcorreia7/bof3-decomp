#include "battle_15.h"

MATCH void func_8009DF70(void) {
    g_BattleTargetRecord->hp_change = -5;
    if ((rand() & 0x7F) < 0x27) {
        func_800A36F0(g_BattleTarget, 0x68);
    }
}
