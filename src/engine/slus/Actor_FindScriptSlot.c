#include "engine/slus/slus.h"

/* Returns code's low six bits plus 0x1E when bit 0x80 is clear. */
/* func_8015B4F4 */
MATCH s8 Actor_FindScriptSlot(s32 code) {
    s8  result;
    s32 index;
    s32 count;
    s32 offset;

    result = code & 0x3F;
    if ((code & 0x80) == 0) {
        result += 0x1E;
    } else {
        index = 0;
        count = 0;
        while ((index & BYTE_MASK) < 30U) {
            offset = (index & BYTE_MASK) * ACTOR_SIZE;
            if (D_8014688E[offset] == 10) {
                if ((count & BYTE_MASK) == (u8)result) {
                    result = count;
                    break;
                }
                count++;
            }
            index++;
        }
    }
    return result;
}
