#include "battle_03.h"

MATCH void func_801E74B8(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801D0F58;
    handlers.handlers[g_Task->header.mode]();
}
