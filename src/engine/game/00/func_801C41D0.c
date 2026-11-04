#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 47.52%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801C41D0(s32 pos_x, s32 pos_y, s16 probe_range) {
    s16   val0;
    s32   val1;
    s32   val2;
    s32   val3;
    s32   val4;
    s32   val5;
    s32   val6;
    s32   val7;
    s32   val8;
    s32   val9;
    s32   val10;
    u32   val11;
    void* tmp0;

    val3 = pos_x;
    val4 = pos_y;
    val0 = probe_range;
    val7 = 1;
    if (!(func_801C3E80(pos_x, pos_y, 1) & BYTE_MASK)) {
        val2 = ((u32)val3 >> 0x10) << 0x10;
        val2 |= 0x8000;
        val1 = ((u32)val4 >> 0x10) << 0x10;
        val1 |= 0x8000;
        if (Area_ReadStepHeight(val2, val1, 4U) >= 0x41) {
            val7 = 1;
            if (SP_REF(u8, 0x0) == 0) {
                goto block_4; /* retail branch */
            }
            return val7;
        }
    block_4:
        val2 &= 0xFFFF0000;
        val2 |= 0x8000;
        val1 &= 0xFFFF0000;
        if (Area_ReadStepHeight(val2, val1, 3U) >= 0x41) {
            val7 = 1;
            if (SP_REF(void*, 0x0) == 0) {
                goto block_7; /* retail branch */
            }
            return val7;
        }
    block_7:
        val2 &= 0xFFFF0000;
        val1 &= 0xFFFF0000;
        val1 |= 0x8000;
        val9 = val3 & HALF_MASK;
        if (Area_ReadStepHeight(val2, val1, 5U) >= 0x41) {
            val7 = 1;
            if (SP_REF(void*, 0x0) == 0) {
                val9 = val3 & HALF_MASK;
                goto block_10; /* retail branch */
            }
            return val7;
        }
    block_10:
        val10 = val4 & HALF_MASK;
        if (val9 == 0) {
            val2 = ((val3 >> 0x10) - 1) << 0x10;
            val2 |= 0x8000;
            val1 = ((u32)val4 >> 0x10) << 0x10;
            if (((Area_ReadStepHeight(val2, val1, 7U) < 0x41) || (val7 = 1, (SP_REF(void*, 0x0) == 0))) &&
                ((val1 &= HALF_MASK, val1 |= ((val4 >> 0x10) + 1) << 0x10,
                  ((Area_ReadStepHeight(val2, val1, 7U) < 0x41) != 0)) ||
                 (val7 = 1, (SP_REF(void*, 0x0) == 0)))) {
                val2 &= HALF_MASK;
                val2 |= ((u32)val3 >> 0x10) << 0x10;
                val1 &= HALF_MASK;
                val1 |= ((val4 >> 0x10) + 1) << 0x10;
                val5 = val3 >> 0x10;
                if (Area_ReadStepHeight(val2, val1, 7U) >= 0x41) {
                    val7 = 1;
                    if (SP_REF(void*, 0x0) == 0) {
                        val5 = val3 >> 0x10;
                        goto block_18; /* retail branch */
                    }
                    return val7;
                }
            block_18:
                val2 = (val5 - 1) << 0x10;
                val1 = ((u32)val4 >> 0x10) << 0x10;
                val1 |= 0x8000;
                if ((Area_ReadStepHeight(val2, val1, 1U) < 0x41) || (val7 = 1, (SP_REF(void*, 0x0) == 0))) {
                    val2 &= HALF_MASK;
                    val2 |= ((val3 >> 0x10) + 1) << 0x10;
                    val10 = val4 & HALF_MASK;
                    if (Area_ReadStepHeight(val2, val1, 1U) >= 0x41) {
                        val7 = 1;
                        if (SP_REF(void*, 0x0) == 0) {
                            val10 = val4 & HALF_MASK;
                            goto block_23; /* retail branch */
                        }
                        return val7;
                    }
                    goto block_23; /* retail branch */
                }
                return val7;
            }
            return val7;
        }
    block_23:
        val6 = val3 & HALF_MASK;
        if (val10 == 0) {
            val1 = ((val4 >> 0x10) - 1) << 0x10;
            val1 |= 0x8000;
            val2 = ((u32)val3 >> 0x10) << 0x10;
            if (((Area_ReadStepHeight(val2, val1, 1U) < 0x41) || (val7 = 1, (SP_REF(void*, 0x0) == 0))) &&
                ((val2 &= HALF_MASK, val2 |= ((val3 >> 0x10) + 1) << 0x10,
                  ((Area_ReadStepHeight(val2, val1, 1U) < 0x41) != 0)) ||
                 (val7 = 1, (SP_REF(void*, 0x0) == 0)))) {
                val1 &= HALF_MASK;
                val1 |= ((u32)val4 >> 0x10) << 0x10;
                val2 &= HALF_MASK;
                val2 |= ((val3 >> 0x10) + 1) << 0x10;
                val11 = (u32)val3 >> 0x10;
                if (Area_ReadStepHeight(val2, val1, 1U) >= 0x41) {
                    val7 = 1;
                    if (SP_REF(void*, 0x0) == 0) {
                        val11 = (u32)val3 >> 0x10;
                        goto block_31; /* retail branch */
                    }
                    return val7;
                }
            block_31:
                val2 = val11 << 0x10;
                val2 |= 0x8000;
                val1 = ((val4 >> 0x10) - 1) << 0x10;
                if ((Area_ReadStepHeight(val2, val1, 3U) < 0x41) || (val7 = 1, (SP_REF(void*, 0x0) == 0))) {
                    val1 &= HALF_MASK;
                    val1 |= ((val4 >> 0x10) + 1) << 0x10;
                    val6 = val3 & HALF_MASK;
                    if (Area_ReadStepHeight(val2, val1, 3U) >= 0x41) {
                        val7 = 1;
                        if (SP_REF(void*, 0x0) == 0) {
                            val6 = val3 & HALF_MASK;
                            goto block_36; /* retail branch */
                        }
                        return val7;
                    }
                    goto block_36; /* retail branch */
                }
                return val7;
            }
            return val7;
        }
    block_36:
        if ((val6 == 0) && !(val4 & HALF_MASK)) {
            val2 = ((val3 >> 0x10) - 1) << 0x10;
            val1 = ((val4 >> 0x10) - 1) << 0x10;
            if (Area_ReadStepHeight(val2 | 0x8000, val1 | 0x8000, 0U) >= 0x41) {
                val7 = 1;
                if (SP_REF(void*, 0x0) == 0) {
                    goto block_41; /* retail branch */
                }
                return val7;
            }
        }
    block_41:
        val8 = Area_ReadHeight(val3, val4) - val0;
        if (val8 < 0) {
            val8 = -val8;
        }
        if (val8 >= 0xC1) {
            return 1;
        }
        tmp0                          = g_SpadWork;
        val1                          = FIELD(u16, tmp0, 0x3Eu);
        FIELD(u16, tmp0, 0x3Eu)       = (u16)val0;
        val7                          = ~func_801BDE14(val3, val4, 1) != 0;
        FIELD(u16, g_SpadWork, 0x3Eu) = (u16)val1;
        return val7;
    }
    return val7;
}
#else
INCLUDE_ASM(func_801C41D0);
#endif
