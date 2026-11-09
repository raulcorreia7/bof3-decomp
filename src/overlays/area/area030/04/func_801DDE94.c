#include "area030_04.h"

/* INFERRED: D_8014412A and D_8014412B are spimdisasm-inferred labels for the bytes stored at 0x8014412A and 0x8014412B, seen only as sb targets here. */

/* Latches the request byte, and when the area state byte holds 4, 6, or 0, flags the transition byte and advances the state byte by one. */
MATCH void func_801DDE94(s8 request) {
    u8* counter;
    u8  state;
    s8  saved;

    saved = request;
    state = D_80144125;
    if ((state == 4) || (state == 6) || (state == 0)) {
        counter    = &D_80144125;
        D_8014412B = 1;
        *counter += 1;
    }
    D_8014412A = saved;
}
