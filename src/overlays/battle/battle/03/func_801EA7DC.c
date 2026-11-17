#include "battle_03.h"

MATCH void func_801EA7DC(void) {
    BattlePanel7Steps table = D_801D1004;

    table.steps[g_MenuCurrentPanel->state]();
}
