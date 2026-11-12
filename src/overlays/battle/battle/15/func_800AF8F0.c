#include "battle_15.h"

MATCH void func_800AF8F0(BattleSpriteCellRecord* record) {
    u8  index;
    u32 quotient;
    u32 remainder;
    u8  base;
    u32 product;
    u32 dividend;
    u32 divisor;
    u32 i;
    u32 clut;

    index     = record->bank_index;
    dividend  = record->cell_value;
    divisor   = s_BattleCellRowDivisor[index];
    quotient  = dividend / divisor;
    remainder = dividend % divisor;
    base      = quotient;
    product   = s_BattleCellRowScale[index] * remainder;
    if (record->flags_24 & 0x4) {
        base = quotient + 0x10;
    }
    for (i = 1; i < (s_BattleCellRowCount[record->bank_index] << 4); i++) {
        clut = (u32)g_GraphicsPaletteDst + ((base & BYTE_MASK) << 9);
        *(u16*)(clut + ((product & BYTE_MASK) + i) * 2) |= 0x8000;
    }
    g_GfxPalettePending = 1;
}
