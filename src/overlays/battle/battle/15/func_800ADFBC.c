#include "battle_15.h"

MATCH void func_800ADFBC(void) {
    if (g_Battle.flags & BATTLE_STATE_AP_PAID) {
        D_800B65FC[SELF(PartyMember)->slot].handler();
    }
}
