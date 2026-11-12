#include "battle_03.h"

/* func_801DE8C0 */
MATCH void Battle_AddMessage(s8 index, s8 record_kind, u8* text) {
    u8  i;
    int off;

    i                 = D_801EC328;
    D_801EB5B0[i * 8] = index;
    i                 = D_801EC328;
    D_801EB5B1[i * 8] = record_kind;
    i                 = D_801EC328;
    off               = (int)(u8)i * 2;
    D_801EB5B4[off]   = text;
    D_801EC328        = (i + 1u) & 0xFu;
}
