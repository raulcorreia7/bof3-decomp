#include "engine/slus/slus.h"

/* 1 when the operand's value equals its selected script variable, else -1. */
MATCH s32 Game_ScriptVarIsEqual(u8* operand) {
    u8 selector;
    u8 value;

    selector = operand[0];
    value    = operand[1];
    if (g_ScriptVars[(selector & SCRIPT_VAR_MASK) >> SCRIPT_VAR_SHIFT] == value) {
        return 1;
    }
    return -1;
}
