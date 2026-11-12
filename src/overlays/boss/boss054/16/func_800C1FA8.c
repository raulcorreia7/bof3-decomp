#include "boss054_16.h"

/* The scratchpad work area is the party member this landing moves; each use reloads the cell. */
#define BOSS054_PARTY ((PartyMember*)g_Task)

MATCH void func_800C1FA8(void) {
    COORD_INT(BOSS054_PARTY->pos.z) += BOSS054_PARTY->unk_14;
    BOSS054_PARTY->unk_14 += BOSS054_PARTY->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x180 to the raw register. */
    if (COORD_INT(BOSS054_PARTY->pos.z) < ((s32 (*)(s32, s32))Area_SampleHeight)(BOSS054_PARTY->pos.x.fixed, BOSS054_PARTY->pos.y.fixed) + 0x180) {
        BOSS054_PARTY->header.step++;
    }
}
