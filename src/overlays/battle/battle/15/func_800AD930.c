#include "battle_15.h"

MATCH void func_800AD930(void) {
    PartyMember* work;
    u8           flag;

    flag = *MEM_PTR(u8, &g_Battle.cursor.panel_entry);
    if (flag != GAME_NONE) {
        work = SELF(PartyMember);
        work->header.step--;
    }
    if (!(g_UIPanelTasks[21].active & 0x1)) {
        SELF(PartyMember)->header.mode++;
        SELF(PartyMember)->header.step = 0;
    }
}
