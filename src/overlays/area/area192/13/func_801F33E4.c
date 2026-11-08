#include "area192_13.h"

MATCH u16 func_801F33E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 index;

    if ((u8)arg3 < 5) {
        index = D_801F38C0[(u8)arg2] + arg0;
    } else {
        index = arg0 + 8;
    }
    return D_801F3890[(u8)index];
}
