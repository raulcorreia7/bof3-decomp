#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 41.36%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801B9F08(u8 arg0, u8 arg1, s8 arg2) {
    u8 buffer[3];
    /* FAKE: retail frame reserves 32 bytes no statement uses. */
    STACK_PADS(u8, 32);
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;
    s32 tmp4;
    s32 val0;
    s32 val1;
    s32 val2;
    s8  val3;
    s32 val4;
    s32 val5;
    s32 val6;
    u32 val7;
    u8* tmp5;
    u8* val8;
    u8* val9;
    u8* val10;
    u8* val11;
    u8* val12;
    u8* limit;
    u8* val13;
    u8* val14;
    u8  tmp6;
    u8  tmp7;
    u8  val15;
    u8  flags;

    val1      = 0;
    val12     = buffer;
    limit     = buffer + 3;
    buffer[0] = arg0;
    buffer[1] = arg1;
    buffer[2] = arg2;
loop_1:
    val0 = val1 & BYTE_MASK;
    if (*val12 != 0) {
        val12 += 1;
        val1 += 1;
        if ((s32)val12 >= (s32)limit) {
            val0 = val1 & BYTE_MASK;
        } else {
            goto loop_1; /* retail branch */
        }
    }
    val5 = 0;
    if (val0 > 0) {
        val10 = buffer;
        do {
            val5 += 1;
            *val10 = SP_REF(u8, *val10);
            val10 += 1;
        } while (val5 < val0);
    }
    val2 = val1 & BYTE_MASK;
    if ((val1 & BYTE_MASK) == 2) {
        val2 = val1 & BYTE_MASK;
        if (buffer[0] == 0x70) {
            val2 = val1 & BYTE_MASK;
            if (buffer[1] == buffer[0]) {
                return 0x70U;
            }
        }
    }
    if (val2 != 0) {
        val13 = buffer;
        do {
            if (*val13 == 0x70) {
                *val13 = 0xFF;
            }
            val13 += 1;
        } while ((s32)val13 < (s32)(buffer + val2));
    }
    tmp3 = val1 & BYTE_MASK;
    if (tmp3 != 0) {
        val14 = buffer;
    loop_18:
        val14 += 1;
        if (*val14 != GAME_NONE) {
            if ((s32)val14 >= (s32)(buffer + tmp3)) {
                goto block_20; /* retail branch */
            }
            goto loop_18; /* retail branch */
        }
        goto block_42; /* retail branch */
    }
block_20:
    tmp2 = val1 & BYTE_MASK;
    val6 = 0;
    if (tmp2 > 0) {
        val11 = buffer;
    loop_22:
        if (*val11 == 0xB0) {
            val6 += 1;
            val11 += 1;
            if (val6 < tmp2) {
                goto loop_22; /* retail branch */
            }
        }
    }
    tmp0 = val1 & BYTE_MASK;
    if (val6 == tmp0) {
        return 0xB0U;
    }
    if (val1 & 1) {
        val3 = 0;
        if (tmp0 != 0) {
            flags = g_SpadWork->direction_08;
            val8  = buffer;
            for (;;) {
                if (!(flags & 1) && (*val8 == 0xA2)) {
                    return 0x10U;
                }
                tmp6 = *val8;
                if (tmp6 == 0xA3) {
                    goto block_42; /* retail branch */
                }
                val3 += 1;
                if (tmp6 == 0xA0) {
                    goto block_42; /* retail branch */
                }
                if (val3 >= tmp0) {
                    goto block_34; /* retail branch */
                }
                val8 += 1;
            }
        }
    block_34:
        if ((val1 & BYTE_MASK) == 1) {
            val7 = val1 & BYTE_MASK;
            if ((buffer[0] & 0xF0) == 0xA0) {
                return buffer[0];
            }
            goto block_50; /* retail branch */
        }
        val7 = val1 & BYTE_MASK;
        goto block_50; /* retail branch */
    }
    if (((buffer[0] & 0xF0) == 0xA0) || (val7 = val1 & BYTE_MASK, ((buffer[1] & 0xF0) == 0xA0))) {
        tmp4 = buffer[0] & BYTE_MASK;
        if ((tmp4 == 0xA2) && (buffer[1] == tmp4)) {
            val15 = 0xA2;
            if (!(g_SpadWork->direction_08 & 1)) {
            block_42:
                return 0x10U;
            }
            return val15;
        }
        if ((buffer[0] == 0xA3) && (buffer[1] == buffer[0])) {
            return 0xA3U;
        }
        tmp1  = buffer[0] & 0xF0;
        val15 = 0x10;
        if ((tmp1 == 0xA0) && ((buffer[1] & 0xF0) == tmp1)) {
            return 0xA1U;
        }
        return val15;
    }
block_50:
    val15 = 0;
    if (val7 >= 2U) {
        val4 = 0;
        if ((val7 - 1) > 0) {
        loop_53:
            tmp5 = buffer + val4;
            if ((*tmp5 & 0xF0) == 0x20) {
                if (val7 != 0) {
                    val9 = buffer;
                loop_56:
                    tmp7 = *val9;
                    if (((tmp7 & 0xF0) != 0x20) || (val15 = 0x20, (*tmp5 == tmp7))) {
                        val9 += 1;
                        if ((s32)val9 >= (s32)(buffer + (val1 & BYTE_MASK))) {
                            goto block_59; /* retail branch */
                        }
                        goto loop_56; /* retail branch */
                    }
                } else {
                block_59:
                    val4 = val1 & BYTE_MASK;
                    goto block_60; /* retail branch */
                }
            } else {
            block_60:
                val4 += 1;
                val7 = val1 & BYTE_MASK;
                if (val4 >= (val7 - 1)) {
                    goto block_61; /* retail branch */
                }
                goto loop_53; /* retail branch */
            }
        } else {
        block_61:
            val15 = 0;
        }
    }
    return val15;
}
#else
INCLUDE_ASM(func_801B9F08);
#endif
