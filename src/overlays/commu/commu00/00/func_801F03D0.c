#include "commu00_00.h"

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
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
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
