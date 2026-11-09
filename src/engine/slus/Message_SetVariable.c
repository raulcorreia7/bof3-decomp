#include "engine/slus/slus.h"

/* The text buffer is an array of 32-byte slots. */

/* copies `length` bytes of `text` into the 32-byte text-buffer slot `slot` and NUL-terminates the copy. */
MATCH void Message_SetVariable(u8 slot, u8 length, const u8* text) {
    u8 i;

    if (length >= 0x20) {
        length = 0x1F;
    }
    for (i = 0; i < length; i++) {
        g_TextVariables[slot][i] = text[i];
    }
    g_TextVariables[slot][i] = 0;
}
