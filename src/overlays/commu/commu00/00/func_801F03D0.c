#include "commu00_00.h"

/* Rolls three distinct labels per row into D_801F2930: each roll is RANDOM_MASK(0x1F), lowered by RANDOM_MASK(0xF)
 * until it fits the row's signed cap, then offset by 0x9B; 0x9F and 0xA0 and repeats are skipped. nonmatching 72.22%:
 * the caps are copied as one 3-byte record (retail lb/sb block copy). The retail keeps &caps in s5 across the row loop
 * and leaves the clamp loop unrotated (test at the top, j back); a goto clamp gives the unrotated shape (73.03%).
 * resume: a loop form GCC does not rotate, then the s5 hoist. */
/* Cap byte of each table row lives in the module header, read signed. */

/* The three label caps, copied as one record. */
typedef struct LabelCaps {
    s8 cap[3];
} LabelCaps;

#ifdef NON_MATCHING
NON_MATCHING void func_801F03D0(void) {
    LabelCaps limits;
    s32       row;
    s32       count;
    s32       i;
    s32       value;
    u16       candidate;
    u8*       cap;

    limits = *(LabelCaps*)D_801EEC08;

    for (row = 0; row < 3; row++) {
        for (count = 2; count >= 0; count--) {
            D_801F2930[row][count] = 0;
        }
    }

    for (row = 0; row < 3; row++) {
        count = 0;
        cap   = (u8*)&limits.cap[row];
        while (count < 3) {
            value = RANDOM_MASK(0x1F);
            for (;;) {
                if (*cap >= (u8)value) {
                    break;
                }
                value -= RANDOM_MASK(0xF);
            }
            candidate = (u8)value + 0x9B;
            for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
                if (candidate == D_801F2930[row][i]) {
                    break;
                }
            }
            if ((u32)(candidate - 0x9F) < 2) {
                continue;
            }
            if (i < 3) {
                continue;
            }
            D_801F2930[row][count] = candidate;
            count++;
        }
    }
}
#else
INCLUDE_ASM(func_801F03D0);
#endif
