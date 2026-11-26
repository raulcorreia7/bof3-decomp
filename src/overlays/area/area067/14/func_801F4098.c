#include "area067_14.h"

MATCH void func_801F4098(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SELF_SET(&g_Game.members[2]);
    index     = g_PartyFieldOrder[2];
    y         = g_Game.members[2].screen_y.signed_value;
    x         = g_Game.members[2].screen_x.signed_value;
    selection = D_801F4644[index];
    result    = Actor_SpawnHelper(3, 0, selection, x, y, g_Game.members[2].pos.z.fixed);
    if ((u8)result != GAME_NONE) {
        SELF(Actor)->param.unk_0B = result;
    }
}
