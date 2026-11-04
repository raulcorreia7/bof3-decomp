#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 27.52%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801B4D7C(u8 wanted_code) {
    s32*  val0;
    s16   tmp0;
    s16   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
    s32   tmp8;
    s32   tmp9;
    s32   val1;
    s32   val2;
    s32   val3;
    s8    tmp10;
    s8    tmp11;
    u16   val4;
    u16   val5;
    u8    tmp12;
    u8    tmp13;
    u8    tmp14;
    u8    tmp15;
    u8    tmp16;
    u8    tmp17;
    u8    val6;
    u8    val7;
    void* tmp18;
    void* tmp19;
    void* tmp20;
    void* tmp21;
    void* tmp22;
    void* tmp23;
    void* tmp24;
    void* tmp25;
    void* tmp26;
    void* tmp27;
    void* tmp28;
    void* tmp29;
    void* val8;

    tmp28 = g_SpadWork;
    val6  = wanted_code;
    if ((FIELD(u16, tmp28, 0x34u) != 0) || (val7 = 0, (FIELD(u16, tmp28, 0x38u) != 0))) {
        tmp26 = g_SpadWork;
        tmp10 = *(D_80181B00 + (FIELD(u8, tmp26, 0x8u) * 2));
        tmp0  = FIELD(s16, tmp26, 0x36u);
        val5  = tmp0 + tmp10;
        if (tmp10 == 1) {
            val5 = tmp0 + 2;
        }
        tmp27 = g_SpadWork;
        tmp11 = *(D_80181B01 + (FIELD(u8, tmp27, 0x8u) * 2));
        tmp1  = FIELD(s16, tmp27, 0x3Au);
        val4  = tmp1 + tmp11;
        if (tmp11 == 1) {
            val4 = tmp1 + 2;
        }
        tmp29 = g_SpadWork;
        val1  = 0;
        if (FIELD(u16, tmp29, 0x34u) != 0) {
            val2 = 1;
            if (FIELD(u16, tmp29, 0x38u) != 0) {
                val0                   = &D_1F800000;
                val8                   = (void*)5;
                GAME_ENTITY_ENTRY_DATA = val4;
                *(u16*)(&D_1F800000)   = FIELD(s16, tmp29, 0x36u);
            loop_9:
                if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
                    (val6 & BYTE_MASK)) {
                    tmp25 = g_SpadWork;
                    tmp17 = FIELD(u8, tmp25, 0x8u);
                    tmp5  = tmp17 & BYTE_MASK;
                    if (tmp17 & 1) {
                        if (tmp5 != 1) {
                            if (tmp5 == 5) {
                                return 1U;
                            }
                            goto block_18; /* retail branch */
                        }
                        goto block_32; /* retail branch */
                    }
                    tmp6 = tmp17 & BYTE_MASK;
                    if ((tmp6 == 0) || (tmp6 == 2)) {
                        FIELD(u8, tmp25, 0x8u) = 1U;
                    } else {
                        FIELD(u8, tmp25, 0x8u) = 5U;
                    }
                    goto block_32; /* retail branch */
                }
            block_18:
                val1 += 1;
                *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
                val3                 = 7;
                if (val1 >= 2) {
                    val1                 = 0;
                    val2                 = 3;
                    val0                 = &D_1F800000;
                    *(u16*)(&D_1F800000) = val5;
                    val8                 = &D_1F800000 + 2;
                    SP_REF(void*, 0x2)   = g_SpadWork->y.part.integer;
                loop_20:
                    if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
                        (val6 & BYTE_MASK)) {
                        tmp18 = g_SpadWork;
                        tmp12 = FIELD(u8, tmp18, 0x8u);
                        tmp2  = tmp12 & BYTE_MASK;
                        if (tmp12 & 1) {
                            if (tmp2 != 7) {
                                if (tmp2 == 3) {
                                    return 1U;
                                }
                                goto block_29; /* retail branch */
                            }
                            goto block_32; /* retail branch */
                        }
                        tmp7 = tmp12 & BYTE_MASK;
                        if ((tmp7 == 0) || (tmp7 == 6)) {
                            FIELD(u8, tmp18, 0x8u) = 7U;
                        } else {
                            FIELD(u8, tmp18, 0x8u) = 3U;
                        }
                        goto block_32; /* retail branch */
                    }
                block_29:
                    val1 += 1;
                    FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
                    if (val1 >= 2) {
                        val1 = val6 & BYTE_MASK;
                        val7 = 1;
                        if (!(func_801B4BE4((g_SpadWork->direction_08 + 2) & 7, (u8)val1) & BYTE_MASK)) {
                            val7 = 0;
                            if (func_801B4BE4((g_SpadWork->direction_08 - 2) & 7, (u8)val1) & BYTE_MASK) {
                                goto block_32; /* retail branch */
                            }
                        }
                        return val7;
                    }
                    goto loop_20; /* retail branch */
                }
                goto loop_9; /* retail branch */
            }
            val3                 = 7;
            val2                 = 3;
            val0                 = &D_1F800000;
            *(u16*)(&D_1F800000) = val5;
            val8                 = &D_1F800000 + 2;
            SP_REF(void*, 0x2)   = (u16)(FIELD(s16, tmp29, 0x3Au) - 1);
        loop_58:
            if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
                (val6 & BYTE_MASK)) {
                tmp22 = g_SpadWork;
                tmp15 = FIELD(u8, tmp22, 0x8u);
                tmp4  = tmp15 & BYTE_MASK;
                if (tmp15 & 1) {
                    if (tmp4 != 7) {
                        if (tmp4 == 3) {
                            return 1U;
                        }
                        goto block_67; /* retail branch */
                    }
                    goto block_32; /* retail branch */
                }
                tmp9 = tmp15 & BYTE_MASK;
                if ((tmp9 == 0) || (tmp9 == 6)) {
                    FIELD(u8, tmp22, 0x8u) = 7U;
                } else {
                    FIELD(u8, tmp22, 0x8u) = 3U;
                }
                goto block_32; /* retail branch */
            }
        block_67:
            val1 += 1;
            FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
            if (val1 >= 3) {
                tmp23 = g_SpadWork;
                tmp16 = FIELD(u8, tmp23, 0x8u);
                if ((tmp16 == 1) || (val7 = 0, (tmp16 == 5))) {
                    val1                 = 0;
                    val0                 = &D_1F800000;
                    *(u16*)(&D_1F800000) = (u16)(FIELD(s16, tmp23, 0x36u) - 1);
                    val8                 = (void*)(val6 & BYTE_MASK);
                    SP_REF(void*, 0x2)   = (u16)(FIELD(s16, tmp23, 0x3Au) - 1);
                loop_71:
                    val1 += 1;
                    if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) !=
                        val8) {
                        FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
                        if (val1 >= 3) {
                            val1                 = 0;
                            tmp24                = g_SpadWork;
                            val0                 = &D_1F800000;
                            *(u16*)(&D_1F800000) = (u16)(FIELD(s16, tmp24, 0x36u) + 2);
                            val8                 = (void*)(val6 & BYTE_MASK);
                            SP_REF(void*, 0x2)   = (u16)(FIELD(s16, tmp24, 0x3Au) - 1);
                        loop_74:
                            val1 += 1;
                            if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) &
                                 BYTE_MASK) != val8) {
                                FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
                                val7                            = 0;
                                if (val1 >= 3) {
                                    return val7;
                                }
                                goto loop_74; /* retail branch */
                            }
                            g_SpadWork->direction_08 = 3U;
                            return 1U;
                        }
                        goto loop_71; /* retail branch */
                    }
                    g_SpadWork->direction_08 = 7U;
                    return 1U;
                }
                return val7;
            }
            goto loop_58; /* retail branch */
        }
        val0                 = &D_1F800000;
        val2                 = 1;
        val8                 = (void*)5;
        SP_REF(void*, 0x2)   = val4;
        *(u16*)(&D_1F800000) = (u16)(FIELD(s16, tmp29, 0x36u) - 1);
    loop_34:
        if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
            (val6 & BYTE_MASK)) {
            tmp19 = g_SpadWork;
            tmp13 = FIELD(u8, tmp19, 0x8u);
            tmp3  = tmp13 & BYTE_MASK;
            if (tmp13 & 1) {
                if (tmp3 != 1) {
                    if (tmp3 == 5) {
                        return 1U;
                    }
                    goto block_43; /* retail branch */
                }
                goto block_32; /* retail branch */
            }
            tmp8 = tmp13 & BYTE_MASK;
            if ((tmp8 == 0) || (tmp8 == 2)) {
                FIELD(u8, tmp19, 0x8u) = 1U;
            } else {
                FIELD(u8, tmp19, 0x8u) = 5U;
            }
        block_32:
            return 1U;
        }
    block_43:
        val1 += 1;
        *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
        if (val1 >= 3) {
            tmp20 = g_SpadWork;
            tmp14 = FIELD(u8, tmp20, 0x8u);
            if ((tmp14 == 7) || (val7 = 0, (tmp14 == 3))) {
                val1                 = 0;
                val0                 = &D_1F800000;
                *(u16*)(&D_1F800000) = (u16)(FIELD(s16, tmp20, 0x36u) - 1);
                val8                 = (void*)(val6 & BYTE_MASK);
                SP_REF(void*, 0x2)   = (u16)(FIELD(s16, tmp20, 0x3Au) - 1);
            loop_47:
                val1 += 1;
                if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) !=
                    val8) {
                    *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
                    if (val1 >= 3) {
                        val1                 = 0;
                        tmp21                = g_SpadWork;
                        val0                 = &D_1F800000;
                        *(u16*)(&D_1F800000) = (u16)(FIELD(s16, tmp21, 0x36u) - 1);
                        val8                 = (void*)(val6 & BYTE_MASK);
                        SP_REF(void*, 0x2)   = (u16)(FIELD(s16, tmp21, 0x3Au) + 2);
                    loop_50:
                        val1 += 1;
                        if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) &
                             BYTE_MASK) != val8) {
                            *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
                            if (val1 >= 3) {
                                return 0U;
                            }
                            goto loop_50; /* retail branch */
                        }
                        g_SpadWork->direction_08 = 5U;
                        return 1U;
                    }
                    goto loop_47; /* retail branch */
                }
                g_SpadWork->direction_08 = 1U;
                return 1U;
            }
            return val7;
        }
        goto loop_34; /* retail branch */
    }
    return val7;
}
#else
INCLUDE_ASM(func_801B4D7C);
#endif
