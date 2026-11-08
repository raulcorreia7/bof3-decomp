#include "area067_14.h"

MATCH void func_801F3F80(void) {
    u8* work;
    u8  index;
    s32 y;
    s32 x;
    u8  selection;
    s32 result;

    TASK_SET(&g_Game.members[0]);
    index     = g_PartyFieldOrder[0];
    y         = g_Game.members[0].pos.y.fixed;
    x         = g_Game.members[0].pos.x.fixed;
    selection = D_801F4644[index];
    result    = func_8015CC00(3, 0, selection, x, y, g_Game.members[0].pos.z.fixed);
    if ((u8)result != GAME_NONE) {
        work      = (u8*)g_Task;
        work[0xB] = result;
    }
}
