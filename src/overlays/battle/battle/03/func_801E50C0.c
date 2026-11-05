#include "battle_03.h"

MATCH void func_801E50C0(void) {
    u8 countdown;

    {
        PartyBattler* work;

        work      = g_Task;
        countdown = work->unk_09;
        if (countdown != 0) {
            work->unk_09 = countdown - 1;
        } else {
            countdown   = work->timer - 1;
            work->timer = countdown;
            if (countdown != 0) {
                g_Task->unk_5D -= 0x10;
                g_Task->unk_5E -= 0x10;
                g_Task->unk_5F -= 0x10;

                {
                    PartyBattler* motion_work;

                    motion_work = g_Task;
                    motion_work->unk_0C += motion_work->unk_18;
                    motion_work->unk_10 += motion_work->unk_1C;
                    motion_work->x.raw += motion_work->unk_0C;
                    motion_work->y.raw += motion_work->unk_10;
                }
                func_801E30F8();
            } else {
                g_Task->step += 1;
            }
        }
    }
}
