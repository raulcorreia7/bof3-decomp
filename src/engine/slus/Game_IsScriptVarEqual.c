#include "engine/slus/slus.h"

/* returns 1 when record[1] equals the table entry selected by record[0],
 * and -1 otherwise.
 */
MATCH s32 Game_IsScriptVarEqual(u8* record) {
    u8 first;
    u8 second;

    first  = record[0];
    second = record[1];
    if (g_ScriptVars[(first & 0xC) >> 2] == second) {
        return 1;
    }
    return -1;
}
