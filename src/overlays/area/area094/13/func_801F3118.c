#include "area094_13.h"

MATCH s32 func_801F3118(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    SELF_SET((u8*)&g_Game.members[1]);
    index     = g_PartyFieldOrder[1];
    y         = g_Game.members[1].screen_y.signed_value;
    x         = g_Game.members[1].screen_x.signed_value;
    selection = (D_801F3504 + 16)[index];
    result    = Actor_ClaimSlot(1, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = SELF(u8);
        work[0xB] = result;
    }
}
