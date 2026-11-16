#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING bool func_801F3CF0(void) {
    PartyMember* member;
    s32          party_size;
    s32          i;
    s32          offset;
    s32          x;
    s32          y;
    s32          delta_x;
    s32          delta_y;

    party_size = g_Game.party_size;
    if (party_size <= 0) {
        return false;
    }

    i = 0;
    do {
        member = &g_Game.members[i];
        x      = (member->pos.x.part.fraction + member->unk_0C * member->unk_09) >> 16;
        y      = (member->pos.y.part.fraction + member->unk_10 * member->unk_09) >> 16;
        offset = 0;
        do {
            delta_x = x - D_801F492C[offset];
            if (delta_x < 0) {
                delta_x = -delta_x;
            }
            delta_y = y - D_801F492D[offset];
            if (delta_y < 0) {
                delta_y = -delta_y;
            }
            if (delta_x < D_801F492E[offset] && delta_y < D_801F492F[offset]) {
                return true;
            }
            offset += 4;
        } while (offset < 16);
        i++;
    } while (i < party_size);
    return false;
}
#else
INCLUDE_ASM(func_801F3CF0);
#endif
