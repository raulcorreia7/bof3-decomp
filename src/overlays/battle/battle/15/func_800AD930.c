#include "battle_15.h"

MATCH void func_800AD930(void) {
    PartyMember* work;
    u8           flag;

    flag = *MEM_PTR(u8, &g_BattlePanelEntry);
    if (flag != GAME_NONE) {
        work = (PartyMember*)g_Task;
        work->header.step--;
    }
    if (!(D_80148624 & 1)) {
        BATTLE_WORK->header.mode++;
        BATTLE_WORK->header.step = 0;
    }
}
