#include "engine/slus/slus.h"

/* returns 1 when the first byte of the record at cursor equals D_80143F03.
 */
MATCH s32 func_8015B6D0(u8** cursor) {
    u8 result; /* the record byte, then the verdict */

    result = **cursor;
    if (D_80143F03 != result) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
