#include "area130_13.h"

MATCH void func_801F3B7C(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET(&D_80145FD0);
    index     = D_80144F5B;
    y         = D_80146000;
    x         = D_80145FFE;
    selection = D_801F3ED8[0x34u + index];
    result    = Actor_ClaimSlot(5, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
