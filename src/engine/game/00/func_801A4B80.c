#include "game_00.h"

MATCH void func_801A4B80(s32 index) {
    s32 off;

    off             = (index & BYTE_MASK) * 0x10;
    D_80147CB9[off] = 0;
    D_80147CBA[off] = 0;
    D_80147CBB[off] = 0;
    D_80147CB8[off] = 0;
}
