#include "area136_13.h"

MATCH void func_801F3048(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SELF_SET((u8*)&g_Game.members[1]);
    index     = g_PartyFieldOrder[1];
    y         = g_Game.members[1].screen_y.signed_value;
    x         = g_Game.members[1].screen_x.signed_value;
    selection = D_801F3424[0xCu + index];
    result    = Actor_ClaimSlot(3, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = SELF(Actor);
        work[0xB] = result;
    }
}
