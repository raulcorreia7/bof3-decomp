#include "game_00.h"

MATCH void func_801C0758(s32 x, s32 y, u8 kind) {
    s32  count;
    s32  index;
    s32  tab;
    s32* y_ptr;
    s32* x_ptr;
    s32  out_y;

    count = 0;
    if (count < g_PartySize) {
        tab   = (kind * 4) & 0x3F8;
        y_ptr = &D_80145EC8;
        x_ptr = y_ptr - 1;
        index = 0;
    loop:
        {
            if ((&D_80145F00)[index] == 0) {
                *x_ptr = x;
                *y_ptr = y;
            } else if ((g_AreaWalkFlags & 0x4000) == 0) {
                *x_ptr = x + FIELD(s32, &D_801CD47C, tab);
                out_y  = y + FIELD(s32, &D_801CD480, tab);
                *y_ptr = out_y;
            } else {
                *x_ptr = x - FIELD(s32, &D_801CD47C, tab);
                out_y  = y - FIELD(s32, &D_801CD480, tab);
                *y_ptr = out_y;
            }
            (&g_BattlePartyBattlers[0].facing)[index] = kind;
            FIELD(s16, &D_80145ECE, index)            = Area_ReadHeight(*x_ptr, *y_ptr);
            if (count != 0) {
                VOL(u8, ((u8*)&g_BattlePartyBattlers[0])[index]) |= 0x40;
            } else {
                g_BattlePartyBattlers[count].header.flags &= ~ACTOR_FLAG_HIDDEN;
            }
            y_ptr += 0x50;
            x_ptr += 0x50;
            index += BATTLE_PARTY_STRIDE;
            count++;
        }
        if (count < g_PartySize) {
            goto loop;
        }
    }
}
