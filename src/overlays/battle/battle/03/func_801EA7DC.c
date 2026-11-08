#include "battle_03.h"

MATCH void func_801EA7DC(void) {
    Panel801D1004States table = D_801D1004;

    table.states[g_MenuCurrentPanel->state]();
}
