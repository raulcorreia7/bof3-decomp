#include "battle_03.h"

MATCH void func_801EA7DC(void) {
    BattleHandlerTable4 table = D_801D1004;

    table.handlers[g_MenuCurrentPanel->state]();
}
