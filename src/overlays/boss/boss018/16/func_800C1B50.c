#include "boss018_16.h"

MATCH void func_800C1B50(void) {
    if (g_Game.members[0].u.turn.command.target == 4) {
        g_Battle.target_selector = 5;
    }
}
