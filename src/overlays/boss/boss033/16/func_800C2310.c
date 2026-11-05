#include "boss033_16.h"

MATCH void func_800C2310(void) {
    volatile u8*  battler;
    PartyBattler* work;
    u8            index;
    s32           delta_x;
    s32           delta_y;
    s32           delta_z;

    if ((func_8014DAEC() & BYTE_MASK) != 0) {
        battler = &g_BattleActiveBattler;
        index   = *battler;
        work    = (PartyBattler*)g_Task;
        delta_x = D_801EB630[index - 3].pos.x.fixed - work->pos.x.fixed;
        if (delta_x < 0) {
            delta_x += 0xF;
        }
        work->unk_0C = delta_x >> 4;
        delta_y      = D_801EB630[*battler - 3].pos.y.fixed - work->pos.y.fixed;
        if (delta_y < 0) {
            delta_y += 0xF;
        }
        work->unk_10 = delta_y >> 4;
        work->unk_14 = 0x40;
        work->unk_20 = -8;
        delta_z      = D_801EB630[*battler - 3].pos.z.fixed - work->pos.z.fixed;
        if (delta_z < 0) {
            delta_z += 0xF;
        }
        work->unk_18 = delta_z >> 4;
        work->step++;
        func_8014DAEC();
    }
}
