#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor equals g_SceneState.state_04.
 */
MATCH s32 func_8015B6A8(u8** cursor) {
    u8 result; /* the record byte, then the verdict */

    result = **cursor;
    /* FAKE: retail reads g_SceneState.state_04 as RecordKey. */
    if ((*(RecordKey*)&g_SceneState.state_04).ubyte != result) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
