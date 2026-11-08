#include "battle_03.h"

MATCH void func_801DF34C(void) {
    volatile PartyMember* work = g_Game.current;

    if (HAS_STATUS(*work, 0x0800u)) {
        Actor_RequestScript(g_Task->facing + 0x34u);
        return;
    }
    Actor_RequestScript(g_Task->facing + 0x10u);
}
