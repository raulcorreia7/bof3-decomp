#include "battle_03.h"

MATCH void func_801DF34C(void) {
    volatile PartyBattler* work = g_GameState;

    if (HAS_STATUS(*work, 0x0800u)) {
        Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x34u);
        return;
    }
    Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x10u);
}
