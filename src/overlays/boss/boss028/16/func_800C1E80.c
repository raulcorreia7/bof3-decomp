#include "boss028_16.h"

/* The scratchpad work area is the party member this landing moves; each use reloads the cell. */
#define BOSS028_PARTY ((PartyMember*)g_Task)

MATCH void func_800C1E80(void) {
    COORD_INT(BOSS028_PARTY->pos.z) += BOSS028_PARTY->unk_14;
    BOSS028_PARTY->unk_14 += BOSS028_PARTY->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x400 to the raw register. */
    if (COORD_INT(BOSS028_PARTY->pos.z) > ((s32 (*)(s32, s32))Area_SampleHeight)(BOSS028_PARTY->pos.x.fixed, BOSS028_PARTY->pos.y.fixed) + 0x400) {
        COORD_INT(BOSS028_PARTY->pos.z) = ((s32 (*)(s32, s32))Area_SampleHeight)(BOSS028_PARTY->pos.x.fixed, BOSS028_PARTY->pos.y.fixed) + 0x400;
        BOSS028_PARTY->unk_14           = 0;
        BOSS028_PARTY->unk_20           = -0x40;
        BOSS028_PARTY->header.step--;
    }
}
