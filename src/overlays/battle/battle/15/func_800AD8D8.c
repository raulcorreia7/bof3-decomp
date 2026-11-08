#include "battle_15.h"

MATCH void func_800AD8D8(void) {
    PartyMember* work;
    u8           flag;

    Actor_SelectScript(0x12);
    /* Plain byte view: this site reads the cell exactly once, so the volatile
     * qualification battle_15.h carries is not needed and would block folding. */
    flag = *MEM_PTR(u8, &g_BattlePanelEntry);
    if (flag == GAME_NONE) {
        Actor_SelectScript(0x13);
        work = (PartyMember*)g_Task;
        work->header.step++;
    }
}
