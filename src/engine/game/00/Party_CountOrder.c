#include "game_00.h"

MATCH u8 Party_CountOrder(u8 mode) {
    s32 index                     = 0;
    /* FAKE: pin holds 0xFF sentinel in a2. */
    MATCH_REG(u8, sentinel, "a2") = 0xFF;
    unsigned int masked           = mode & sentinel;
    u8*          base             = D_80144F5A;
    s32          off              = (s32)masked * 3;
    u8*          ptr              = base + off;

    while (index < 3) {
        if (*ptr == sentinel) {
            break;
        }
        index++;
        ptr++;
    }
    return index;
}
