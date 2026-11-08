#include "battle_03.h"

MATCH void func_801E7818(void) {
    BattleSavedPreviewFuncs table = D_801D0F6C;

    table.handlers[g_Task->header.mode]();
}
