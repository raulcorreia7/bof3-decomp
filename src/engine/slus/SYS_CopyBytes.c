#include "engine/slus/slus.h"

/* copies count bytes from src to dst, front to back.
 */
/* func_80177CD4 */
MATCH void SYS_CopyBytes(u8* dst_base, u8* src_base, s32 count) {
    u8* dst;
    u8* src;
    s32 left;
    u8  value;

    dst  = dst_base;
    src  = src_base;
    left = count - 1;
    do {
        if (left == -1) {
            break;
        }
        value = *src;
        src += 1;
        left -= 1;
        *dst = value;
        dst += 1;
    } while (1);
}
