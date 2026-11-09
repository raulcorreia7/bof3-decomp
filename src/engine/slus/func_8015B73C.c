#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor equals the leader's character id. */
MATCH s32 func_8015B73C(u8** cursor) {
    u8 result; /* the record byte, then the verdict */

    result = **cursor;
    if (g_Game.members[0].chr.character_id != result) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
