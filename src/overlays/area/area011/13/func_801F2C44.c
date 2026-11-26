#include "area011_13.h"

MATCH void func_801F2C44(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SELF_SET(g_Game.members);
    index     = g_PartyFieldOrder[2];
    y         = g_Game.members[0].screen_y.signed_value;
    x         = g_Game.members[0].screen_x.signed_value;
    selection = D_801F2D78[index];
    result    = Actor_ClaimSlot(1, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        SELF(Actor)->param.unk_0B = result;
    }
}
