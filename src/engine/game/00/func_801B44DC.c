#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 18.24%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801B44DC(u8 wanted_code) {
    s32*  val0;
    s16   tmp0;
    s16   tmp1;
    s16   tmp2;
    s16   val1;
    s16   val2;
    s16   val3;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
    s32   tmp8;
    s32   tmp9;
    s32   tmp10;
    s32   tmp11;
    s32   tmp12;
    s32   tmp13;
    s32   val4;
    s32   val5;
    s8    val6;
    u16   tmp14;
    u16   tmp15;
    u16   tmp16;
    u8    tmp17;
    u8    tmp18;
    u8    tmp19;
    u8    tmp20;
    u8    tmp21;
    u8    tmp22;
    u8    val7;
    void* tmp23;
    void* tmp24;
    void* tmp25;
    void* tmp26;
    void* tmp27;
    void* tmp28;
    void* tmp29;
    void* tmp30;
    void* tmp31;
    void* tmp32;
    void* tmp33;
    void* tmp34;

    tmp33 = g_SpadWork;
    val7  = wanted_code;
    if ((FIELD(u16, tmp33, 0x34u) == 0) || (FIELD(u16, tmp33, 0x38u) == 0)) {
        tmp27 = g_SpadWork;
        tmp17 = FIELD(u8, tmp27, 0x8u);
        tmp16 = FIELD(u16, tmp27, 0x36u);
        tmp11 = tmp17 * 2;
        val1  = tmp16 + (s8) * (D_80181B00 + tmp11);
        val3  = val1;
        tmp0  = FIELD(u16, tmp27, 0x3Au) + (s8) * (D_80181B01 + tmp11);
        val2  = tmp0;
        if (FIELD(u16, tmp27, 0x34u) == 0) {
            if (FIELD(u16, tmp27, 0x38u) == 0) {
                val0                            = &D_1F800000;
                val0                            = &D_1F800000;
                *(u16*)(&D_1F800000)            = tmp16;
                FIELD(s16, (&D_1F800000), 0x2u) = val2;
                val7 &= BYTE_MASK;
                if ((Area_GetCellCode(FIELD(u16, tmp27, 0x36u), tmp0) & BYTE_MASK) == val7) {
                    tmp31                           = g_SpadWork;
                    FIELD(s16, (&D_1F800000), 0x2u) = val2;
                    *(u16*)(&D_1F800000)            = FIELD(u16, tmp31, 0x36u);
                    tmp22                           = FIELD(u8, tmp31, 0x8u);
                    if (tmp22 & 1) {
                        tmp12 = tmp22 & BYTE_MASK;
                        if (tmp12 != 1) {
                            if (tmp12 == 5) {
                                return 1U;
                            }
                            return 0U;
                        }
                        goto block_23; /* retail branch */
                    }
                    tmp13 = tmp22 & BYTE_MASK;
                    val6  = 1;
                    if (tmp13 != 0) {
                        if (tmp13 == 2) {
                            val6 = 1;
                        } else {
                            val6 = 5;
                        }
                    }
                    goto block_22; /* retail branch */
                }
                if ((Area_GetCellCode(val1, FIELD(u16, g_SpadWork, 0x3Au)) & BYTE_MASK) == val7) {
                    tmp23                           = g_SpadWork;
                    *(u16*)(&D_1F800000)            = (u16)val3;
                    FIELD(s16, (&D_1F800000), 0x2u) = FIELD(u16, tmp23, 0x3Au);
                    tmp18                           = FIELD(u8, tmp23, 0x8u);
                    if (tmp18 & 1) {
                        tmp6 = tmp18 & BYTE_MASK;
                        if (tmp6 != 7) {
                            if (tmp6 == 3) {
                                return 1U;
                            }
                            return 0U;
                        }
                        goto block_23; /* retail branch */
                    }
                    tmp7 = tmp18 & BYTE_MASK;
                    val6 = 7;
                    if (tmp7 != 0) {
                        if (tmp7 == 6) {
                            val6 = 7;
                        } else {
                            val6 = 3;
                        }
                    }
                block_22:
                    FIELD(s8, g_SpadWork, 0x8u) = val6;
                    goto block_23; /* retail branch */
                }
                tmp32 = g_SpadWork;
                tmp19 = FIELD(u8, tmp32, 0x8u);
                if (tmp19 & 1) {
                    val1                            = (tmp19 + 2) & 7;
                    tmp8                            = val1 * 2;
                    tmp14                           = FIELD(u16, tmp32, 0x36u) + (s8) * (D_80181B00 + tmp8);
                    *(u16*)(&D_1F800000)            = tmp14;
                    tmp1                            = FIELD(u16, tmp32, 0x3Au) + (s8) * (D_80181B01 + tmp8);
                    FIELD(s16, (&D_1F800000), 0x2u) = tmp1;
                    if (((Area_GetCellCode((s16)tmp14, tmp1) & BYTE_MASK) == val7) ||
                        (tmp34 = g_SpadWork, val1 = (FIELD(u8, tmp34, 0x8u) - 2) & 7, tmp3 = val1 * 2,
                         tmp15 = FIELD(u16, tmp34, 0x36u) + (s8) * (D_80181B00 + tmp3), *(u16*)(&D_1F800000) = tmp15,
                         tmp2                            = FIELD(u16, tmp34, 0x3Au) + (s8) * (D_80181B01 + tmp3),
                         FIELD(s16, (&D_1F800000), 0x2u) = tmp2,
                         ((Area_GetCellCode((s16)tmp15, tmp2) & BYTE_MASK) == val7))) {
                        g_SpadWork->direction_08 = (u8)val1;
                        return 1U;
                    }
                    return 0U;
                }
                goto block_73; /* retail branch */
            }
            if (tmp17 != 1) {
                val1 = 0;
                if (tmp17 != 5) {
                    val5                   = 7;
                    val4                   = 3;
                    val0                   = &D_1F800000;
                    *(u16*)(&D_1F800000)   = (u16)val3;
                    val2                   = (s16)(&D_1F800000 + 2);
                    GAME_ENTITY_ENTRY_DATA = FIELD(u16, tmp27, 0x3Au);
                loop_52:
                    if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
                        (val7 & BYTE_MASK)) {
                        tmp28 = g_SpadWork;
                        tmp21 = FIELD(u8, tmp28, 0x8u);
                        tmp5  = tmp21 & BYTE_MASK;
                        if (tmp21 & 1) {
                            if (tmp5 != 7) {
                                if (tmp5 == 3) {
                                    return 1U;
                                }
                                goto block_61; /* retail branch */
                            }
                            goto block_23; /* retail branch */
                        }
                        tmp10 = tmp21 & BYTE_MASK;
                        if ((tmp10 == 0) || (tmp10 == 6)) {
                            FIELD(u8, tmp28, 0x8u) = 7U;
                        } else {
                            FIELD(u8, tmp28, 0x8u) = 3U;
                        }
                        goto block_23; /* retail branch */
                    }
                block_61:
                    val1 += 1;
                    GAME_ENTITY_ENTRY_DATA = (u16)(GAME_ENTITY_ENTRY_DATA + 1);
                    if (val1 >= 2) {
                        return 0U;
                    }
                    goto loop_52; /* retail branch */
                }
            }
            val1                 = 0;
            tmp29                = g_SpadWork;
            val0                 = &D_1F800000;
            *(u16*)(&D_1F800000) = (u16)(FIELD(u16, tmp29, 0x36u) - 1);
            val2                 = val7 & BYTE_MASK;
            SP_REF(void*, 0x2)   = FIELD(u16, tmp29, 0x3Au);
        loop_68:
            val1 += 1;
            if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) != val2) {
                FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
                if (val1 >= 2) {
                    val1                 = 0;
                    tmp30                = g_SpadWork;
                    val0                 = &D_1F800000;
                    *(u16*)(&D_1F800000) = (u16)(FIELD(u16, tmp30, 0x36u) + 1);
                    val2                 = val7 & BYTE_MASK;
                    SP_REF(void*, 0x2)   = FIELD(u16, tmp30, 0x3Au);
                loop_71:
                    val1 += 1;
                    if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) !=
                        val2) {
                        FIELD(s16, (&D_1F800000), 0x2u) = (s16)(FIELD(s16, (&D_1F800000), 0x2u) + 1);
                        if (val1 >= 2) {
                        block_73:
                            return 0U;
                        }
                        goto loop_71; /* retail branch */
                    }
                    g_SpadWork->direction_08 = 3U;
                    return 1U;
                }
                goto loop_68; /* retail branch */
            }
            g_SpadWork->direction_08 = 7U;
            return 1U;
        }
        if (tmp17 != 7) {
            val1 = 0;
            if (tmp17 != 3) {
                val0                 = &D_1F800000;
                val5                 = 1;
                val4                 = 5;
                *(u16*)(&D_1F800000) = tmp16;
                SP_REF(void*, 0x2)   = (u16)val2;
            loop_31:
                if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) ==
                    (val7 & BYTE_MASK)) {
                    tmp24 = g_SpadWork;
                    tmp20 = FIELD(u8, tmp24, 0x8u);
                    tmp4  = tmp20 & BYTE_MASK;
                    if (tmp20 & 1) {
                        if (tmp4 != 1) {
                            if (tmp4 == 5) {
                                return 1U;
                            }
                            goto block_40; /* retail branch */
                        }
                        goto block_23; /* retail branch */
                    }
                    tmp9 = tmp20 & BYTE_MASK;
                    if ((tmp9 == 0) || (tmp9 == 2)) {
                        FIELD(u8, tmp24, 0x8u) = 1U;
                    } else {
                        FIELD(u8, tmp24, 0x8u) = 5U;
                    }
                block_23:
                    return 1U;
                }
            block_40:
                val1 += 1;
                *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
                if (val1 >= 2) {
                    return 0U;
                }
                goto loop_31; /* retail branch */
            }
        }
        val1                 = 0;
        tmp25                = g_SpadWork;
        val0                 = &D_1F800000;
        *(u16*)(&D_1F800000) = FIELD(u16, tmp25, 0x36u);
        val2                 = val7 & BYTE_MASK;
        SP_REF(void*, 0x2)   = (u16)(FIELD(u16, tmp25, 0x3Au) - 1);
    loop_43:
        val1 += 1;
        if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) != val2) {
            *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
            if (val1 >= 2) {
                val1                 = 0;
                tmp26                = g_SpadWork;
                val0                 = &D_1F800000;
                *(u16*)(&D_1F800000) = FIELD(u16, tmp26, 0x36u);
                val2                 = val7 & BYTE_MASK;
                SP_REF(void*, 0x2)   = (u16)(FIELD(u16, tmp26, 0x3Au) + 1);
            loop_46:
                val1 += 1;
                if ((Area_GetCellCode((s16) * (u16*)(&D_1F800000), FIELD(s16, (&D_1F800000), 0x2u)) & BYTE_MASK) !=
                    val2) {
                    *(u16*)(&D_1F800000) = (u16)(*(u16*)(&D_1F800000) + 1);
                    if (val1 >= 2) {
                        return 0U;
                    }
                    goto loop_46; /* retail branch */
                }
                g_SpadWork->direction_08 = 5U;
                return 1U;
            }
            goto loop_43; /* retail branch */
        }
        g_SpadWork->direction_08 = 1U;
        return 1U;
    }
    return 0U;
}
#else
INCLUDE_ASM(func_801B44DC);
#endif
