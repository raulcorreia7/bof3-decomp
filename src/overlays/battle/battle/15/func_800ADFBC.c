#include "battle_15.h"

MATCH void func_800ADFBC(void) {
    if (g_Battle.state & BATTLE_STATE_AP_PAID) {
        D_800B65FC[BATTLE_WORK->slot].handler();
    }
}
