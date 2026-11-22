#include "battle_15.h"

MATCH void func_800AD930(void) {
    PartyMember* work;
    u8           flag;

    flag = *MEM_PTR(u8, &g_Battle.cursor.panel_entry);
    if (flag != GAME_NONE) {
        work = TASK(PartyMember);
        work->header.step--;
    }
    if (!(D_80148624 & 0x1)) {
        TASK(PartyMember)->header.mode++;
        TASK(PartyMember)->header.step = 0;
    }
}
