#include "game_00.h"

MATCH s32 func_801C090C(s32 anchor_x, s32 anchor_y, s32 anchor_index) {
    u8   count;
    s32  x;
    s32  y;
    s32  i;
    s32  off;
    s32* x_ptr;
    s32* p;

    count = g_Game.party_size;
    if (count >= 2U) {
        x_ptr                         = &D_80145EC4;
        x                             = anchor_x + FIELD(s32, &D_801CD47C, (anchor_index * 4) & 0x3F8) * 2;
        *x_ptr                        = x;
        y                             = anchor_y + FIELD(s32, &D_801CD480, (anchor_index * 4) & 0x3F8) * 2;
        g_Game.members[0].pos.y.fixed = y;
        if (g_Game.members[0].unk_70 != 0) {
            *x_ptr                        = x + FIELD(s32, &D_801CD47C, (anchor_index * 4) & 0x3F8);
            g_Game.members[0].pos.y.fixed = y + FIELD(s32, &D_801CD480, (anchor_index * 4) & 0x3F8);
        }
        g_Game.members[0].facing = anchor_index;
        for (i = 1, off = BATTLE_PARTY_STRIDE; i < count; i++, off += BATTLE_PARTY_STRIDE) {
            /* FAKE: allocation-steering copy into dead y. */
            y = off;
            if ((&g_Game.members[0].unk_70)[y] != 0) {
                p = &D_80145EC4;
                *p += FIELD(s32, &D_801CD47C, (anchor_index * 4) & 0x3F8);
                D_80145EC8 += FIELD(s32, &D_801CD480, (anchor_index * 4) & 0x3F8);
                break;
            }
        }
    } else {
        g_Game.members[0].pos.x.fixed = anchor_x;
        g_Game.members[0].pos.y.fixed = anchor_y;
        g_Game.members[0].facing      = anchor_index;
    }
}
