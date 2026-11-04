#include "battle_15.h"

MATCH void func_800A8678(void) {
    u8* work;
    u32 offset;
    u32 value;

    work = g_SpadWork;
    if (FIELD(s32, work, 0x3C) < FIELD(s32, work, 0x20)) {
        FIELD(s32, work, 0x3C) = FIELD(s32, work, 0x3C) + 0x01000000;
    } else {
        if (g_BattleTargetSelector >= 3u) {
            FIELD(s32, work, 0x34) = g_AreaScrollTargetX + ((s8*)D_800B44C0)[g_BattleScrollDir * 2];
            offset                 = g_BattleScrollDir * 2;
        } else {
            FIELD(u8, work, 0x8) ^= 2u;
            value                  = g_AreaScrollTargetX + ((s8*)D_800B44C0)[(g_BattleScrollDir ^ 2) * 2];
            work                   = g_SpadWork;
            FIELD(s32, work, 0x34) = value;
            offset                 = (g_BattleScrollDir ^ 2) * 2;
        }
        FIELD(s32, work, 0x38) = g_AreaScrollTargetY + ((s8*)D_800B44C0)[offset + 1];
        Actor_SelectScript((BATTLE_WORK->word_08.byte.unk_08 + 0x40) & BYTE_MASK);
        BATTLE_WORK->step_01++;
    }
    func_801DEE4C();
}
