#include "boss018_16.h"

MATCH void func_800C19B4(void) {
    if (g_BattlePartyBattlers[0].u.turn.command.target == 4) {
        g_BattleTargetSelector = 5;
    }
}
