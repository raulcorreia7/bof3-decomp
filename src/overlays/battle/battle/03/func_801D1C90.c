#include "battle_03.h"

MATCH void func_801D1C90(void) {
    int index = 0;
    func_801DB494();
    func_801DA7D4();
    g_BattleCommandCount = index;
    if (g_BattleState & BATTLE_STATE_COMMAND_ARMED) {
        func_801DD29C();
        g_BattleMode = 2;
        return;
    }
    func_801DE1D4();
    g_BattleStep++;
}
