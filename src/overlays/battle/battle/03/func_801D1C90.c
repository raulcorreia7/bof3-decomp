#include "battle_03.h"

MATCH void func_801D1C90(void) {
    int index = 0;
    func_801DB494();
    func_801DA7D4();
    g_Battle.command_count = index;
    if (g_Battle.state & BATTLE_STATE_COMMAND_ARMED) {
        func_801DD29C();
        g_Battle.phase.mode = 2;
        return;
    }
    func_801DE1D4();
    g_Battle.phase.step++;
}
