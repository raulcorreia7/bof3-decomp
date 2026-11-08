#include "battle_03.h"

MATCH void func_801E74B8(void) {
    BattleEffect4Steps handlers;

    handlers = D_801D0F58;
    handlers.steps[g_Task->header.mode]();
}
