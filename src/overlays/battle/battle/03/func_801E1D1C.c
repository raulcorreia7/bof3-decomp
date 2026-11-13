#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_IsReady() != 0) {
        Actor_RequestScript(g_Task->facing + 0x24u);
        Battle_IsPartyMemberBlocked();
        g_Task->header.step += 1;
    }
}
