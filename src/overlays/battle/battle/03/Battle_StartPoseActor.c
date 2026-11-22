#include "battle_03.h"

/* func_801E679C */
MATCH void Battle_StartPoseActor(void) {
    PartyMember* work;
    u8*          table;

    BATTLE_WORK->unk_29 = 0;
    BATTLE_WORK->unk_25 = 0x1D;
    BATTLE_WORK->unk_26 = 0;
    BATTLE_WORK->unk_24 = 0x84;
    BATTLE_WORK->unk_27 = D_801EB4A4[BATTLE_WORK->unk_07] + 0xB0;
    BATTLE_WORK->unk_28 = 0;
    work                = g_Task;
    work->unk_2B        = 0;
    work->unk_2C.value  = 0;
    if (BATTLE_WORK->unk_07 != 6) {
        if ((u32)(BATTLE_WORK->facing - 1) < 2) {
            BATTLE_WORK->unk_2A = 1;
        } else {
            BATTLE_WORK->unk_2A = 0;
        }
    } else if (BATTLE_WORK->facing & 0x1) {
        BATTLE_WORK->unk_2A = 1;
    } else {
        BATTLE_WORK->unk_2A = 0;
    }
    BATTLE_WORK->header.mode = BATTLE_WORK->header.mode + 1;
    table                    = D_801EB4B0 + (BATTLE_WORK->unk_07 << 1);
    Script_Select(table[BATTLE_WORK->facing >> 1]);
    Area_AddActor();
}
