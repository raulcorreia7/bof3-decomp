#include "boss054_16.h"

/* The scratchpad work area is the party member this landing moves; each use reloads the cell. */

MATCH void func_800C1FA8(void) {
    COORD_INT(SELF(PartyMember)->pos.z) += SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x180 to the raw register. */
    if (COORD_INT(SELF(PartyMember)->pos.z) < ((s32 (*)(s32, s32))Area_HeightSample)(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed) + 0x180) {
        SELF(PartyMember)->header.step++;
    }
}
