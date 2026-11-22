#include "engine/slus/slus.h"

/* Returns code's low six bits plus 0x1E when bit 0x80 is clear; with the bit set it scans the 30 actor
 * records for the key-th row whose mode byte is 10 and returns the key.
 */
/* func_8015B4F4 */
MATCH s8 Script_FindSlot(s32 code) {
    s8  result;
    s32 index;
    s32 count;

    result = code & 0x3F;
    if ((code & 0x80) == 0) {
        result += 0x1E;
    } else {
        index = 0;
        count = 0;
        while ((index & BYTE_MASK) < 30U) {
            if (g_Actors[index & BYTE_MASK].unk_06 == 10) {
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
