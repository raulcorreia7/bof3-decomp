#include "engine/slus/slus.h"

/* returns 1 when g_SceneRecord.ubyte is at most the first byte of the record at cursor.
 */
MATCH s32 Game_IsScenarioAtMost(u8** cursor) {
    u32 result;

    result = **cursor;
    if (g_SceneRecord.ubyte <= result) {
        /* the global is at or below the record byte */
        goto one;
    }
    result = 0;
    return result;
one:
    result = 1;
    return result;
}
