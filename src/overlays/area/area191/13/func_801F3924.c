#include "area191_13.h"

MATCH u16 func_801F3924(s32 base, s32 arg1, s32 row, s32 mode) {
    u32 index;

    if ((u8)mode < 5) {
        index = D_801F4290[(u8)row] + base;
    } else {
        index = base + 8;
    }
    return D_801F4260[(u8)index];
}
