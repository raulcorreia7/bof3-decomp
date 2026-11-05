#include "battle_15.h"

MATCH void func_800AD930(void) {
    PartyBattler* work;
    u8            flag;

    flag = *MEM_PTR(u8, &g_BattlePanelEntry);
    if (flag != GAME_NONE) {
        work = (PartyBattler*)g_Task;
        work->step--;
    }
    if (!(D_80148624 & 1)) {
        BATTLE_WORK->mode++;
        BATTLE_WORK->step = 0;
    }
}
