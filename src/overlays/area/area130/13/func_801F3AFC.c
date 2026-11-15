#include "area130_13.h"

MATCH void func_801F3AFC(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET(&D_80146110);
    index     = D_80144F5C;
    y         = D_80146140;
    x         = D_8014613E;
    selection = D_801F3ED8[0x34u + index];
    result    = Actor_ClaimSlot(4, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
