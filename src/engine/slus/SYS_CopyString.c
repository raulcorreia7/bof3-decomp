#include "engine/slus/slus.h"

/* copies at most (limit & 0xFF) bytes from src to dst, stopping at a
 * NUL byte, and NUL-terminates the destination.
 */
MATCH void SYS_CopyString(u8* dst, u8* src, s32 limit) {
    u32 count;
    u32 index;
    u8  value;

    count = limit & BYTE_MASK;
    index = 0;
    if (count != 0) {
        do {
            value = *src;
            if (value == 0) {
                break;
            }
            *dst = value;
            src += 1;
            index += 1;
            dst += 1;
        } while ((index & BYTE_MASK) < count);
    }
    *dst = 0;
}
