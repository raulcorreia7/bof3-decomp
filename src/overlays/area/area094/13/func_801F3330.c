#include "area094_13.h"

MATCH void func_801F3330(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;
    u8* work;

    SELF_SET((u8*)&g_Game.members[2]);
    index     = g_PartyFieldOrder[2];
    y         = g_Game.members[2].screen_y.signed_value;
    x         = g_Game.members[2].screen_x.signed_value;
    selection = (D_801F3504 + 8)[index];
    result    = Actor_ClaimSlot(4, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        work      = SELF(u8);
        work[0xB] = result;
    }
}
