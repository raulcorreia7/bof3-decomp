#include "engine/slus/slus.h"

MATCH s32 Game_ScriptVarSet(u8* operand) {
    g_ScriptVars[(operand[0] & SCRIPT_VAR_MASK) >> SCRIPT_VAR_SHIFT] = operand[1];
    return 1;
}
