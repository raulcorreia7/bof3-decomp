#include "engine/slus/slus.h"

/* The text buffer is an array of 32-byte slots: the shop call sites pass slot
 * 0 with a byte length of 8 or 0xC, and the length clamp below (0x20 -> 0x1F) is
 * what leaves room for the terminator. The row view is the shape the retail
 * address tree needs (`(base + slot * 0x20) + i`, measured). */

/* copies `length` bytes of `text` into the 32-byte text-buffer slot
 * `slot` and NUL-terminates the copy; a length of 32 or more is clamped to 31
 * so the terminator still fits the slot.
 */
MATCH void TEXT_SetVariable(u8 slot, u8 length, const u8* text) {
    u8 i;

    if (length >= 0x20) {
        length = 0x1F;
    }
    for (i = 0; i < length; i++) {
        g_TextVariables[slot][i] = text[i];
    }
    g_TextVariables[slot][i] = 0;
}
