#include "battle_03.h"

MATCH void func_801E6724(void) {
    Callback handlers[2] = {func_801E679C, func_801E68EC};

    g_ScriptBank = BATTLE_SCRIPT_BANK;
    handlers[TASK_BYTES[1]]();
    g_ScriptBank = AREA_SCRIPT_BANK;
}
