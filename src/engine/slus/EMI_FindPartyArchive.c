#include "engine/slus/slus.h"

/* 51.52%; branch@+0x000C: pointer setup and the 3-byte search loop diverge. */
#ifdef NON_MATCHING
NON_MATCHING u8 EMI_FindPartyArchive(u8 member_a, u8 member_b, u8 member_c) {
    s32       i;
    u8        c;
    u8*       q;
    u8*       hp;
    const u8* p;
    s32       j;
    s32       val0;
    s32       val1;
    s32       val2;
    s32       val3;
    s32       val4;
    s32       val5;
    s32       val6;
    s32       val7;
    s32       val8;
    s32       val9;
    s32       val10;
    s32       val11;
    s32       val12;
    s32       val13;
    u8*       val14;
    u8*       val15;
    u8*       val16;
    const u8* val17;
    const u8* val18;
    u8        tmp0;
    u8        tmp1;
    u8        tmp2;
    const u8* val19;
    const u8* val20;

    hp              = &g_EmiLoadedCharacterIndex;
    q               = D_1F800000;
    *q              = member_a;
    SP_REF(s8, 0x1) = member_b;
    SP_REF(s8, 0x2) = member_c;
    if (*hp != GAME_NONE) {
        for (i = 0; i < 3; i++, q++) {
            c = *q;
            if (c != GAME_NONE) {
                p = D_80181B34[0] + (*hp & 0x7F) * 3;
                for (j = 0; j < 3; j++, p++) {
                    if (c == *p) {
                        break;
                    }
                }
                if (j >= 3) {
                    break;
                }
            }
        }
        if (i >= 3) {
            return g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK;
        }
    }
    val4 = 0;
    val8 = 0;
    do {
        if (D_1F800000[val4] != GAME_NONE) {
            val8 += 1;
        }
        val4 += 1;
    } while (val4 < 3);
    val5  = 0;
    val16 = D_1F800000;
    do {
        val2 = val5 + 1;
        if (val2 < 3) {
            val14 = &D_1F800000[val5 + 1];
            do {
                tmp2 = *val16;
                if ((u8)*val14 < tmp2) {
                    D_1F800004 = tmp2;
                    *val16     = *val14;
                    *val14     = D_1F800004;
                }
                val2 += 1;
                val14 += 1;
            } while (val2 < 3);
        }
        val5 += 1;
        val16 += 1;
    } while (val5 < 2);
    val11 = 0;
    val7  = 0x13;
    val9  = 0;
    val10 = 0xFF;
    val3  = 0;
    val0  = 0 & BYTE_MASK;
loop_24:
    val6 = val10 & BYTE_MASK;
    if (val0 < (val7 & BYTE_MASK)) {
        val17 = &D_1F800000[val9];
        val19 = (val0 * 3) + D_80181B34[0];
    loop_26:
        tmp1 = *val17;
        if (tmp1 == *(val19 + val3)) {
            if (val9 == ((val8 & BYTE_MASK) - 1)) {
                val10 = val0;
            } else {
                val11 = val0;
                if (val0 < 0x13) {
                    val20 = (val0 * 3) + D_80181B34[0];
                loop_31:
                    if (tmp1 == *(val20 + val3)) {
                        val20 += 3;
                        val0 += 1;
                        val19 += 3;
                        if (val0 < 0x13) {
                            goto loop_31; /* retail branch */
                        }
                    }
                }
                val7 = val0;
                val17 += 1;
                val9 += 1;
                goto block_34; /* retail branch */
            }
        } else {
        block_34:
            val0 += 1;
            val19 += 3;
            if (val0 < (val7 & BYTE_MASK)) {
                goto loop_26; /* retail branch */
            }
        }
        val6 = val10 & BYTE_MASK;
    }
    val3 += 1;
    if (val6 == GAME_NONE) {
        val0 = val11 & BYTE_MASK;
        if (val3 >= 3) {
            SYS_ShowFileNotFound();
        } else {
            goto loop_24; /* retail branch */
        }
    }
    return val6;
}
#else
INCLUDE_ASM(EMI_FindPartyArchive);
#endif
