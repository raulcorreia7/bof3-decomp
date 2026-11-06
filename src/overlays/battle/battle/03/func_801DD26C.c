#include "battle_03.h"

MATCH void func_801DD26C(s8 arg0) {
    volatile u8* b             = &D_80146322;
    s32          temp          = b[0] - 1;
    b[0]                       = temp;
    (&D_8014630C)[temp & 0xFF] = arg0;
}
