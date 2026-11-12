#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s8 func_801F34F8(s32 x, s32 y) {
    PartyMember* member;
    s32          dx;
    s32          dy;
    s32          i;
    s32          radius;

    for (i = 0; i < g_Game.party_size; i++) {
        member = &g_Game.members[i];
        if (member->header.flags == 0) {
            continue;
        }
        radius = (member->unk_70 + 2) << 15;
        dx     = member->pos.x.fixed + member->unk_0C * member->unk_09 - TO_COORD(x);
        dy     = member->pos.y.fixed + member->unk_10 * member->unk_09 - TO_COORD(y);
        if (abs(dx) < radius && abs(dy) < radius) {
            return i;
        }
    }
    return -1;
}
#else
INCLUDE_ASM(func_801F34F8);
#endif
