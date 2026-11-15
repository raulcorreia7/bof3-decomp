#include "area134_13.h"

MATCH void func_801F52D0(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET((u8*)&g_Game.members[1]);
    index     = g_PartyFieldOrder[1];
    y         = g_Game.members[1].unk_30.signed_half;
    x         = g_Game.members[1].unk_2E.signed_half;
    selection = D_801F5724[0x144u + index];
    result    = Actor_ClaimSlot(3, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
