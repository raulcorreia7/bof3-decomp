#include "battle_15.h"

MATCH void func_800A8A28(void) {
    volatile u8* battler;
    PartyMember* work;
    u8           index;
    s32          delta_x;
    s32          delta_y;
    s32          delta_z;

    if ((func_801DEE4C() & BYTE_MASK) != 0) {
        battler = &g_Battle.active_battler;
        index   = *battler;
        work    = (PartyMember*)g_Task;
        delta_x = g_Game.members[index].pos.x.fixed - work->pos.x.fixed;
        if (delta_x < 0) {
            delta_x += 0xF;
        }
        work->unk_0C = delta_x >> 4;
        delta_y      = g_Game.members[*battler].pos.y.fixed - work->pos.y.fixed;
        if (delta_y < 0) {
            delta_y += 0xF;
        }
        work->unk_10 = delta_y >> 4;
        work->unk_14 = 0x40;
        work->unk_20 = -8;
        delta_z      = g_Game.members[*battler].pos.z.fixed - work->pos.z.fixed;
        if (delta_z < 0) {
            delta_z += 0xF;
        }
        work->unk_18 = delta_z >> 4;
        work->header.mode++;
        func_801DEE4C();
    }
}
