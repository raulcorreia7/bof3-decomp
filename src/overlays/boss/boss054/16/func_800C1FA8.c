#include "boss054_16.h"

/* The scratchpad work area is the party member this landing moves; each use reloads the cell. */

MATCH void func_800C1FA8(void) {
    COORD_INT(TASK(PartyMember)->pos.z) += TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14 += TASK(PartyMember)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x180 to the raw register. */
    if (COORD_INT(TASK(PartyMember)->pos.z) < ((s32 (*)(s32, s32))Area_HeightSample)(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) + 0x180) {
        TASK(PartyMember)->header.step++;
    }
}
