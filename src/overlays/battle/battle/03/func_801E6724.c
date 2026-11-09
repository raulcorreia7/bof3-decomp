#include "battle_03.h"

MATCH void func_801E6724(void) {
    Callback handlers[2] = {func_801E679C, func_801E68EC};

    g_ScriptTable = BATTLE_SCRIPT_BANK;
    handlers[g_Task->header.mode]();
    g_ScriptTable = AREA_SCRIPT_BANK;
}
