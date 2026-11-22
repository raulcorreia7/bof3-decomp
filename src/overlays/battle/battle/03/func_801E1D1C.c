#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_IsReady() != 0) {
        Script_Request(BATTLE_WORK->facing + 0x24u);
        Battle_IsPartyMemberBlocked();
        BATTLE_WORK->header.step += 1;
    }
}
