/* best score 90.14 */
#include "shared/etc.h"

/* start_08.h declares Party_CountOrder as u8(u8); this unit reads the count as a full register. */
u8 Party_CountOrder(u8 mode);

extern s8  D_801484E1;
extern s8  D_801484E2;
extern s8  D_801484E3;
extern s16 D_801484E4;
extern s16 D_801484E6;
extern u8* D_80148500;
extern u8  D_80148658;
extern u8  D_80148659;
extern u8  D_8014865A;
extern u8  D_8014865D;
extern u8  D_801ED690[];
extern u8  D_801ED694[][2];
extern u8  D_801ED695[][2];
extern u8  D_801ED69C;

/* nonmatching unmeasured: tried 88.03%: signed s32 loops over 8 records of stride 0xA4, volatile pointer to D_801484EA,
 * for-loop blez guards, offset pinned a3, stack padding dropped; falsified: explicit j biv (85.21), 15 min of rewrite search
 * (type hacks). resume: j must be a preheader-initialised biv with addiu v1,v1,2 in the branch delay slot and i++ after
 * the volatile load. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DAE14(void) {
    s32 count;
    /* FAKE: pin keeps the row offset in the retail a3 home. */
    MATCH_REG(s32, offset, "a3");
    s32          i;
    s32          index;
    s32          j;
    volatile u8* flags;
    volatile u8* total;

    count  = Party_CountOrder(0);
    flags  = &D_801484EA;
    *flags = 0;
    offset = 0;
    for (i = 0; i < 8; i++) {
        if (((u8*)&g_Characters[0].unk_07)[offset] & 1) {
            for (index = 0; index < (count & BYTE_MASK); index++) {
                if (g_Characters[i].character_index == D_80144F5A[index]) {
                    break;
                }
            }
            if (index == (count & BYTE_MASK)) {
                D_801ED690[(*flags)++] = g_Characters[i].character_index;
            }
        }
        offset += 0xA4;
    }

    D_801484E0 = 1;
    D_801484E1 = 6;
    D_801484E2 = 0x13;
    D_801484E3 = 2;
    D_801484E4 = BATTLE_PARTY_STRIDE;
    D_801484E6 = 0x3B;
    D_80148500 = D_801ED690;

    for (i = 0; i < (count & BYTE_MASK); i++) {
        D_801ED694[i][0] = 1;
    }
    for (; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        D_801ED694[i][0] = 0;
    }

    total = &D_801484EA;
    for (i = 0; i < *total; i++) {
        D_801ED695[i][0] = 1;
    }
    for (; i < *total; i++) {
        D_801ED695[i][0] = 0;
    }

    D_8014865A = 0x7F;
    D_8014865D = 0x7F;
    D_80148658 = 0;
    D_80148659 = 0;
    D_801ED69C = 0xFF;
}
#else
INCLUDE_ASM(func_801DAE14);
#endif
