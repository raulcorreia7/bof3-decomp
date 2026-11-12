#include "battle_03.h"

MATCH void func_801DEC28(u8* out, u8* text, s32 width, s32 max_chars) {
    s32 used;
    s32 pad;
    u32 copy_len;
    u32 max_len;
    u8* text_start;
    u8* dst;
    u8* src;
    u8  ch;

    dst        = out;
    src        = text;
    used       = 0;
    max_len    = max_chars & BYTE_MASK;
    text_start = src;
    if (max_len != 0) {
    count_next:
        if (*src++ != 0) {
            used += 1;
            if ((used & BYTE_MASK) < max_len) {
                /* next source byte */
                goto count_next;
            }
        }
    }
    pad = (((width & BYTE_MASK) - (used & BYTE_MASK)) / 2) + (used & 0x1);
    if (pad & BYTE_MASK) {
        do {
            dst += 1;
            pad -= 1;
            *dst = 0xFF;
        } while (pad & BYTE_MASK);
    }
    src      = text_start;
    copy_len = max_chars & BYTE_MASK;
    used     = 0;
    if (copy_len != 0) {
    copy_next:
        ch = *src;
        if (ch != 0) {
            *dst = ch;
            src += 1;
            used += 1;
            dst += 1;
            if ((used & BYTE_MASK) < copy_len) {
                /* next copied byte */
                goto copy_next;
            }
        }
    }
    *dst = 0;
}
