#include "area094_13.h"

MATCH void func_801F3050(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    TASK_SET((u8*)g_Game.members);
    index     = g_PartyFieldOrder[0];
    y         = g_Game.members[0].unk_30.signed_half;
    x         = g_Game.members[0].unk_2E.signed_half;
    selection = (D_801F3504 + 8)[index];
    result    = Actor_ClaimSlot(4, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
