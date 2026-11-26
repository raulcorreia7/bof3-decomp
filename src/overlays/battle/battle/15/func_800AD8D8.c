#include "battle_15.h"

MATCH void func_800AD8D8(void) {
    PartyMember* work;
    u8           flag;

    Script_Select(0x12);
    /* Plain byte view: this site reads the cell exactly once, so the volatile
     * qualification battle_15.h carries is not needed and would block folding. */
    flag = *MEM_PTR(u8, &g_Battle.cursor.panel_entry);
    if (flag == GAME_NONE) {
        Script_Select(0x13);
        work = SELF(PartyMember);
        work->header.step++;
    }
}
