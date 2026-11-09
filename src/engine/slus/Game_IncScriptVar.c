#include "engine/slus/slus.h"

/* increments the table entry selected by operand[0] and returns 0.
 */
MATCH s32 Game_IncScriptVar(u8* operand) {
    g_ScriptVars[(operand[0] & 0xC) >> 2] += 1;
    return 0;
}
