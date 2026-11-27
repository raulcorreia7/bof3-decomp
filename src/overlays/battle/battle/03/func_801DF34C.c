#include "battle_03.h"

MATCH void func_801DF34C(void) {
    volatile PartyMember* work = g_Game.current;

    if (HAS_STATUS(*work, 0x0800u)) {
        Script_Request(SELF(PartyMember)->facing + 0x34u);
        return;
    }
    Script_Request(SELF(PartyMember)->facing + 0x10u);
}
