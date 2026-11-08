#include "area067_14.h"

MATCH void func_801F400C(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET(&g_Game.members[1]);
    index     = g_PartyFieldOrder[1];
    y         = g_Game.members[1].unk_30.signed_half;
    x         = g_Game.members[1].unk_2E.signed_half;
    selection = D_801F4644[index];
    result    = func_8015CC00(3, 0, selection, x, y, g_Game.members[1].pos.z.fixed);
    if ((u8)result != GAME_NONE) {
        g_Task->param.unk_0B = result;
    }
}
