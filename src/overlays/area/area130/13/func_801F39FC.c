#include "area130_13.h"

MATCH void func_801F39FC(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SP_REF(u8*, 0x44u) = &D_80146110;
    index              = D_80144F5C;
    y                  = D_80146140;
    x                  = D_8014613E;
    selection          = D_801F3ED8[0x28u + index];
    result             = func_8015CB18(1, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = (u8*)g_Task;
        work[0xB] = (u8)result;
    }
}
