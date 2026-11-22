#include "battle_03.h"

/* func_801E679C */
MATCH void Battle_StartPoseActor(void) {
    PartyMember* work;
    u8*          table;

    TASK(PartyMember)->unk_29 = 0;
    TASK(PartyMember)->unk_25 = 0x1D;
    TASK(PartyMember)->unk_26 = 0;
    TASK(PartyMember)->unk_24 = 0x84;
    TASK(PartyMember)->unk_27 = D_801EB4A4[TASK(PartyMember)->unk_07] + 0xB0;
    TASK(PartyMember)->unk_28 = 0;
    work                      = g_Task;
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    if (TASK(PartyMember)->unk_07 != 6) {
        if ((u32)(TASK(PartyMember)->facing - 1) < 2) {
            TASK(PartyMember)->unk_2A = 1;
        } else {
            TASK(PartyMember)->unk_2A = 0;
        }
    } else if (TASK(PartyMember)->facing & 0x1) {
        TASK(PartyMember)->unk_2A = 1;
    } else {
        TASK(PartyMember)->unk_2A = 0;
    }
    TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    table                          = D_801EB4B0 + (TASK(PartyMember)->unk_07 << 1);
    Script_Select(table[TASK(PartyMember)->facing >> 1]);
    Area_AddActor();
}
