#include "battle_03.h"

MATCH void func_801E50C0(void) {
    u8 countdown;

    {
        PartyBattler* work;

        work      = g_SpadWork;
        countdown = work->word_08.byte.unk_09;
        if (countdown != 0) {
            work->word_08.byte.unk_09 = countdown - 1;
        } else {
            countdown                   = work->word_08.byte.timer_0A - 1;
            work->word_08.byte.timer_0A = countdown;
            if (countdown != 0) {
                g_SpadWork->unk_5D -= 0x10;
                g_SpadWork->unk_5E -= 0x10;
                g_SpadWork->unk_5F -= 0x10;

                {
                    PartyBattler* motion_work;

                    motion_work = g_SpadWork;
                    motion_work->unk_0C += motion_work->unk_18;
                    motion_work->unk_10 += motion_work->unk_1C;
                    motion_work->coord_x_34.raw += motion_work->unk_0C;
                    motion_work->coord_y_38.raw += motion_work->unk_10;
                }
                func_801E30F8();
            } else {
                g_SpadWork->unk_02 += 1;
            }
        }
    }
}
