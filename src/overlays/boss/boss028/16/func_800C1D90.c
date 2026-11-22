#include "boss028_16.h"

MATCH void func_800C1D90(void) {
    COORD_INT(BOSS028_PARTY->pos.z) += BOSS028_PARTY->unk_14;
    BOSS028_PARTY->unk_14 += BOSS028_PARTY->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x200 to the raw register. */
    if (COORD_INT(BOSS028_PARTY->pos.z) < ((s32 (*)(s32, s32))Area_HeightSample)(BOSS028_PARTY->pos.x.fixed, BOSS028_PARTY->pos.y.fixed) + 0x200) {
        COORD_INT(BOSS028_PARTY->pos.z) = ((s32 (*)(s32, s32))Area_HeightSample)(BOSS028_PARTY->pos.x.fixed, BOSS028_PARTY->pos.y.fixed) + 0x200;
        BOSS028_PARTY->unk_14           = 0;
        BOSS028_PARTY->unk_20           = 0x40;
        SND_QueueSelectionSE(0x600);
        if (BOSS028_PARTY->unk_09 != 0) {
            BOSS028_PARTY->unk_09--;
            BOSS028_PARTY->header.step += 1;
        } else {
            BOSS028_PARTY->header.step += 2;
        }
    }
}
