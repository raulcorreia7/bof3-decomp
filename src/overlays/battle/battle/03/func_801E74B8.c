#include "battle_03.h"

MATCH void func_801E74B8(void) {
    Effect801D0F58Steps handlers;

    handlers = D_801D0F58;
    handlers.steps[g_Task->header.mode]();
}
