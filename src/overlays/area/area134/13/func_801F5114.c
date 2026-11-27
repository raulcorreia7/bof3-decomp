#include "area134_13.h"

MATCH void func_801F5114(void) {
    u8* work;
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    SELF_SET((u8*)g_Game.members);
    index     = g_PartyFieldOrder[0];
    y         = g_Game.members[0].screen_y.signed_value;
    x         = g_Game.members[0].screen_x.signed_value;
    selection = D_801F5724[0x150u + index];
    result    = Actor_ClaimSlot(4, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        work      = SELF(u8);
        work[0xB] = result;
    }
}
