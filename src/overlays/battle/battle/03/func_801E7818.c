#include "battle_03.h"

MATCH void func_801E7818(void) {
    BattleSavedPreviewModes table = D_801D0F6C;

    table.modes[g_Task->header.mode]();
}
