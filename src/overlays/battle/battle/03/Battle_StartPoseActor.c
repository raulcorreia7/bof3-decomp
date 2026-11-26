#include "battle_03.h"

/* func_801E679C */
MATCH void Battle_StartPoseActor(void) {
    PartyMember* work;
    u8*          table;

    SELF(PartyMember)->unk_29 = 0;
    SELF(PartyMember)->unk_25 = 0x1D;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_24 = 0x84;
    SELF(PartyMember)->unk_27 = D_801EB4A4[SELF(PartyMember)->unk_07] + 0xB0;
    SELF(PartyMember)->unk_28 = 0;
    work                      = SELF(PartyMember);
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    if (SELF(PartyMember)->unk_07 != 6) {
        if ((u32)(SELF(PartyMember)->facing - 1) < 2) {
            SELF(PartyMember)->unk_2A = 1;
        } else {
            SELF(PartyMember)->unk_2A = 0;
        }
    } else if (SELF(PartyMember)->facing & 0x1) {
        SELF(PartyMember)->unk_2A = 1;
    } else {
        SELF(PartyMember)->unk_2A = 0;
    }
    SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    table                          = D_801EB4B0 + (SELF(PartyMember)->unk_07 << 1);
    Script_Select(table[SELF(PartyMember)->facing >> 1]);
    Area_AddActor();
}
