#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor equals g_GameAreaId.
 */
MATCH s32 Game_IsAreaEqual(u8** cursor) {
    u8 result; /* the record byte, then the verdict */

    result = **cursor;
    if (g_GameAreaId != result) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
