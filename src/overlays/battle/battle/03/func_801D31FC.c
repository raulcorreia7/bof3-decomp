#include "battle_03.h"

MATCH void func_801D31FC(void) {
    func_801D4850();
    func_801DE560(1, 0, 0, 0x1E, D_801EB082);
    g_BattleMessageState = 1;
    Battle_SetSlotPending(g_BattleActingBattler);
    D_8014637C->step_01 = 9;
    g_BattleUiStep += 1;
}
