#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor equals g_ScriptVars[3].
 */
MATCH s32 Game_IsScriptVar3Equal(u8** cursor) {
    u8 result; /* the record byte, then the verdict */

    result = **cursor;
    if (g_ScriptVars[3] != result) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
