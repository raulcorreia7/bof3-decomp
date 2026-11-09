#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor is >= g_SceneState.
 */
MATCH s32 Game_IsScenarioAtLeast(u8** cursor) {
    u32 result;

    result = **cursor;
    if (g_SceneRecord.ubyte <= result) {
        /* the record byte is at or above the global */
        goto one;
    }
    result = 0;
    return result;
one:
    result = 1;
    return result;
}
