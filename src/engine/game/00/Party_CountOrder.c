#include "game_00.h"

MATCH u8 Party_CountOrder(u8 order) {
    s32 index                    = 0;
    /* FAKE: pin holds 0xFF sentinel in a2. */
    FAKE_REG(u8, sentinel, "a2") = 0xFF;
    unsigned int masked          = order & sentinel;
    u8*          base            = g_PartyFieldOrder;
    s32          off             = masked * 3;
    u8*          ptr             = base + off;

    while (index < 3) {
        if (*ptr == sentinel) {
            break;
        }
        index++;
        ptr++;
    }
    return index;
}
