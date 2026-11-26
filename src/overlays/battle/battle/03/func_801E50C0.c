#include "battle_03.h"

MATCH void func_801E50C0(void) {
    u8 countdown;

    {
        PartyMember* work;

        work      = SELF(PartyMember);
        countdown = work->unk_09;
        if (countdown != 0) {
            work->unk_09 = countdown - 1;
        } else {
            countdown   = work->timer - 1;
            work->timer = countdown;
            if (countdown != 0) {
                SELF(PartyMember)->unk_5D -= 0x10;
                SELF(PartyMember)->unk_5E -= 0x10;
                SELF(PartyMember)->unk_5F -= 0x10;

                {
                    PartyMember* motion_work;

                    motion_work = SELF(PartyMember);
                    motion_work->unk_0C += motion_work->unk_18;
                    motion_work->unk_10 += motion_work->unk_1C;
                    motion_work->pos.x.fixed += motion_work->unk_0C;
                    motion_work->pos.y.fixed += motion_work->unk_10;
                }
                Battle_IsEnemyBlocked();
            } else {
                SELF(PartyMember)->header.step += 1;
            }
        }
    }
}
