#include "engine/slus/slus.h"

typedef union PaletteTint {
    u32 raw;
    s8  bytes[4];
} PaletteTint;

/* reads one palette-tint record: when its tag at +0 resolves through func_80155E7C it forwards the mask
 * halves at +4 and the three signed colour deltas at +8 to func_8015822C; an unresolved tag sends the same masks with
 * zero deltas.
 */
MATCH void Area_ReadTintRecord(u8* record) {
    PaletteTint value;
    u32         masks;
    u32         lo;
    u32         hi;
    s32         red;
    s32         green;
    s32         blue;
    s8          found;

    found = Area_TestCondition(*(s16*)record);
    record += 4;
    masks = *(u32*)record;
    record += 4;
    lo = masks & HALF_MASK;
    hi = masks >> 16;
    if (found) {
        value.raw = *(u32*)record;
        red       = value.bytes[0];
        green     = value.bytes[1];
        blue      = value.bytes[2];
    } else {
        blue  = 0;
        green = 0;
        red   = 0;
    }
    Area_ApplyPaletteTint(lo, hi, red, green, blue);
}
