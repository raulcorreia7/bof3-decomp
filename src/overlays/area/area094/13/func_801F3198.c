#include "area094_13.h"

MATCH void func_801F3198(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    TASK_SET((u8*)&g_Game.members[2]);
    index     = g_PartyFieldOrder[2];
    y         = g_Game.members[2].unk_30.signed_half;
    x         = g_Game.members[2].unk_2E.signed_half;
    selection = (D_801F3504 + 16)[index];
    result    = Actor_ClaimSlot(1, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
