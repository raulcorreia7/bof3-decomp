#include "game_00.h"

extern s32 func_801BB1B8(s32 arg0);

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 70.97%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801BA678(void) {
    u8     buf[16];
    s16    val0;
    s16    tmp0;
    s16    tmp1;
    s16    tmp2;
    s16    tmp3;
    s16    tmp4;
    s16    tmp5;
    s16    tmp6;
    s16    tmp7;
    s16    val1;
    s16    val2;
    s16    val3;
    s16    val4;
    s16    val5;
    s16    val6;
    s16    val7;
    s16    val8;
    s32    tmp8;
    s32    tmp9;
    s32    tmp10;
    s32    tmp11;
    s32    val9;
    s32    val10;
    s8     tmp12;
    s8     tmp13;
    s16    val11;
    s16    val12;
    s8     val13;
    s8     val14;
    u16    tmp14;
    u8     tmp15;
    u8     tmp16;
    u8     tmp17;
    u8     tmp18;
    u8     tmp19;
    u8     tmp20;
    u8     tmp21;
    u8     val15;
    u8     val16;
    u8     val17;
    u8     val18;
    u8     val19;
    u8     val20;
    u8*    spad;
    u8     collision_axis;
    void*  tmp22;
    void*  tmp23;
    Actor* tmp24;
    void*  tmp25;
    void*  tmp26;
    void*  tmp27;
    void*  tmp28;
    void*  tmp29;

    if ((0x400 & g_GameFlags) ||
        ((tmp24 = g_SpadWork, val20 = FIELD(u8, tmp24, 0x8u), (FIELD(u16, tmp24, 0x34u) == 0)) &&
         (FIELD(u16, tmp24, 0x38u) == 0))) {
        return 1;
    }
    tmp12 = *(D_80181B00 + (g_SpadWork->direction_08 * 2));
    val12 = (tmp12 == 1) ? 2 : tmp12;
    val7  = val12;
    tmp13 = *(D_80181B01 + (g_SpadWork->direction_08 * 2));
    val11 = (tmp13 == 1) ? 2 : tmp13;
    tmp14 = FIELD(u16, g_SpadWork, 0x36u);
    val4  = (s16)tmp14;
    val7  = val4 + val12;
    val8  = FIELD(u16, g_SpadWork, 0x3Au) + val11;
    if ((*(D_80181B00 + (g_SpadWork->direction_08 * 2)) + 1) == 2) {
        val4 += 1;
    }
    val6 = g_SpadWork->y.part.integer;
    if ((*(D_80181B01 + (g_SpadWork->direction_08 * 2)) + 1) == 2) {
        val6 += 1;
    }
    func_801BBCCC(val7, val8, val4, val6);
    tmp15 = g_SpadWork->direction_08;
    if (!(tmp15 & 1)) {
        if (g_SpadWork->x.part.fraction != 0) {
            if (g_SpadWork->y.part.fraction != 0) {
                val10   = 5;
                spad    = SP_PTR(u8, 0x8u);
                spad[0] = func_801BA278(1U, 2U, 3U, 4U, 5U);
                spad[1] = func_801BA278(4U, 5U, 0U, 0U, 0U);
                tmp16   = func_801BA278(2U, 3U, 0U, 0U, 0U);
                spad[2] = tmp16;
                if (spad[0] != 0xB0) {
                    if (spad[1] == 0x70) {
                        val15 = 4;
                        val17 = 6;
                        val19 = 5;
                        goto block_20; /* retail branch */
                    }
                    val15 = 2;
                    if ((tmp16 & BYTE_MASK) == 0x70) {
                        val17 = 4;
                        val19 = 3;
                    block_20:
                        func_801BB8E8(val15, val17, val19);
                        goto block_21; /* retail branch */
                    }
                    if (!(func_801BB1B8(2) & BYTE_MASK)) {
                        if ((((spad[1] & 0xF0) != 0xA0) ||
                             ((tmp19 = g_SpadWork->direction_08, val9 = 9, (tmp19 != 1)) && (tmp19 != 5))) &&
                            (((spad[2] & 0xF0) != 0xA0) ||
                             ((tmp20 = g_SpadWork->direction_08, val9 = 0xA, (tmp20 != 3)) && (tmp20 != 7)))) {
                            if ((spad[1] & 0xF0) == 0xA0) {
                                g_SpadWork->direction_08 = val20;
                                func_801BB8E8(4U, 6U, 5U);
                                val9 = 9;
                                goto block_109; /* retail branch */
                            }
                            if ((spad[2] & 0xF0) == 0xA0) {
                                g_SpadWork->direction_08 = val20;
                                func_801BB8E8(2U, 4U, 3U);
                                val9 = 0xA;
                                goto block_109; /* retail branch */
                            }
                            func_801BB9B4(val7, val8);
                            return 3;
                        }
                        goto block_109; /* retail branch */
                    }
                    return 0;
                }
                goto block_95; /* retail branch */
            }
            tmp17           = func_801BA278(3U, 2U, 6U, 0U, 0U);
            tmp10           = tmp17 & BYTE_MASK;
            SP_REF(u8, 0x8) = tmp17;
            switch (tmp10) { /* switch 1; irregular */
                case 0x10:   /* switch 1 */
                case 0x20:   /* switch 1 */
                    func_801BB8E8(4U, 6U, 5U);
                    /* fallthrough */
                default: /* switch 1 */
                    if ((SP_REF(u8, 0x8u) & 0xF0) == 0xA0) {
                        val9 = 8;
                        if (!(1 & g_SpadWork->direction_08)) {
                            func_801BB8E8(2U, 4U, 3U);
                            val9 = 8;
                        }
                        goto block_109; /* retail branch */
                    }
                    tmp25 = g_SpadWork;
                    if (!(1 & FIELD(u8, tmp25, 0x8u))) {
                        val0 = val7;
                        tmp4 = FIELD(u16, tmp25, 0x3Au);
                        val7 = 1;
                        if (func_801BB86C(val0, val0, tmp4, (s16)(tmp4 + 1), val7) & BYTE_MASK) {
                            func_801BB8E8(4U, 6U, 5U);
                        }
                        tmp26 = g_SpadWork;
                        if (!(1 & FIELD(u8, tmp26, 0x8u))) {
                            tmp5 = FIELD(u16, tmp26, 0x3Au);
                            if (func_801BB86C(val0, val0, tmp5, (s16)(tmp5 - 1), val7) & BYTE_MASK) {
                                func_801BB8E8(4U, 6U, 5U);
                                return 3;
                            }
                            goto block_114; /* retail branch */
                        }
                        return 3;
                    }
                    return 3;
            }
        } else {
            tmp18            = func_801BA278(5U, 4U, 7U, 0U, 0U);
            tmp11            = tmp18 & BYTE_MASK;
            SP_REF(u8, 0x8u) = tmp18;
            switch (tmp11) { /* switch 2; irregular */
                case 0x10:   /* switch 2 */
                case 0x20:   /* switch 2 */
                    func_801BB8E8(2U, 4U, 3U);
                    /* fallthrough */
                default: /* switch 2 */
                    if ((SP_REF(u8, 0x8u) & 0xF0) == 0xA0) {
                        val9 = 8;
                        if (!(1 & g_SpadWork->direction_08)) {
                            func_801BB8E8(4U, 6U, 5U);
                            val9 = 8;
                        }
                        goto block_109; /* retail branch */
                    }
                    tmp27 = g_SpadWork;
                    if (!(1 & FIELD(u8, tmp27, 0x8u))) {
                        val0 = val8;
                        tmp0 = FIELD(u16, tmp27, 0x36u);
                        val7 = 3;
                        if (func_801BB86C(tmp0, (s16)(tmp0 + 1), val0, val0, val7) & BYTE_MASK) {
                            func_801BB8E8(2U, 4U, 3U);
                        }
                        tmp28 = g_SpadWork;
                        if (!(1 & FIELD(u8, tmp28, 0x8u))) {
                            tmp1 = FIELD(u16, tmp28, 0x36u);
                            if (func_801BB86C(tmp1, (s16)(tmp1 - 1), val0, val0, val7) & BYTE_MASK) {
                                func_801BB8E8(2U, 4U, 3U);
                                return 3;
                            }
                            goto block_114; /* retail branch */
                        }
                        return 3;
                    }
                    return 3;
            }
        }
    } else if (g_SpadWork->x.part.fraction != 0) {
        tmp9 = tmp15 & 2;
        if (g_SpadWork->y.part.fraction != 0) {
            val16 = 2;
            if (tmp9 != 0) {
                val18 = 3;
            } else {
                val16 = 4;
                val18 = 5;
            }
            SP_REF(u8, 0x8u) = func_801BA278(val16, val18, 0U, 0U, 0U);
            tmp21            = SP_REF(u8, 0x8u);
            tmp8             = tmp21 & BYTE_MASK;
            if (tmp8 == 0x10 || tmp8 == 0x20) {
                goto block_74; /* retail branch */
            }
            switch (tmp8) { /* switch 3; irregular */
                default:    /* switch 3 */
                    if ((tmp21 & 0xF0) != 0xA0) {
                        tmp29 = g_SpadWork;
                        if (2 & FIELD(u8, tmp29, 0x8u)) {
                            val1           = val7;
                            val2           = val1;
                            val3           = FIELD(u16, tmp29, 0x3Au);
                            val5           = val3 + 1;
                            collision_axis = 1;
                        } else {
                            val3           = val8;
                            val5           = val3;
                            val1           = FIELD(u16, tmp29, 0x36u);
                            val2           = val1 + 1;
                            collision_axis = 3;
                        }
                        if (func_801BB86C(val1, val2, val3, val5, collision_axis) & BYTE_MASK) {
                            goto block_74; /* retail branch */
                        }
                        return 3;
                    }
                    goto block_108; /* retail branch */
            }
        } else if (tmp9 != 0) {
            SP_REF(u8, 0x8u) = func_801BA278(3U, 2U, 6U, 0U, 0U);
            SP_REF(u8, 0x9u) = func_801B9F08(3, 0, 0);
            SP_REF(u8, 0xAu) = func_801B9F08(6, 0, 0);
            SP_REF(u8, 0xBu) = func_801B9F08(2, 0, 0);
            switch (SP_REF(u8, 0x8u)) {
                case 0x20: /* switch 4 */
                    if ((SP_REF(u8, 0x2u) & 0xF0) != SP_REF(u8, 0x8u)) {
                        case 0x10: /* switch 4 */
                            spad = SP_PTR(u8, 0xBu);
                            if (spad[0] != 0x10) {
                                if (!(func_801BB934(9, 0xA, 1, 0x10) & BYTE_MASK)) {
                                    if (spad[0] == 0xA2) {
                                        val13 = 5;
                                    } else {
                                        val13 = 1;
                                    }
                                    if (!(func_801BB934(9, 0xA, val13, 0xA2) & BYTE_MASK)) {
                                        default: /* switch 4 */
                                            val9 = 8;
                                            if ((SP_REF(u8, 0x8u) & 0xF0) != 0xA0) {
                                                val0 = val7;
                                                tmp6 = FIELD(u16, g_SpadWork, 0x3Au);
                                                val7 = 1;
                                                if (func_801BB86C(val0, val0, tmp6, tmp6 + 1, val7) & BYTE_MASK) {
                                                    g_SpadWork->direction_08 = 1U;
                                                    return 1;
                                                }
                                                tmp7 = FIELD(u16, g_SpadWork, 0x3Au);
                                                if (func_801BB86C(val0, val0, tmp7, tmp7 + (-1), val7) & BYTE_MASK) {
                                                    g_SpadWork->direction_08 = 5U;
                                                    return 1;
                                                }
                                                goto block_114; /* retail branch */
                                            }
                                            goto block_109; /* retail branch */
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            goto block_74; /* retail branch */
                    }
                    return 0;
            }
        } else {
            goto block_114; /* retail branch */
        }
    } else {
        if (!(tmp15 & 2)) {
            SP_REF(u8, 0x8u) = func_801BA278(5U, 4U, 7U, 0U, 0U);
            SP_REF(u8, 0x9u) = func_801B9F08(5, 0, 0);
            SP_REF(u8, 0xAu) = func_801B9F08(7, 0, 0);
            SP_REF(u8, 0xBu) = func_801B9F08(4, 0, 0);
            switch (SP_REF(u8, 0x8u)) {
                case 0x70: /* switch 5 */
                block_21:
                    return 7;
                case 0xB0: /* switch 5 */
                block_95:
                    return 6;
                case 0x20: /* switch 5 */
                    if ((SP_REF(u8, 0x4u) & 0xF0) != SP_REF(u8, 0x8u)) {
                        case 0x10: /* switch 5 */
                            spad = SP_PTR(u8, 0xBu);
                            if (spad[0] != 0x10) {
                                if (!(func_801BB934(9, 0xA, 7, 0x10) & BYTE_MASK)) {
                                    if (spad[0] == 0xA2) {
                                        val14 = 3;
                                    } else {
                                        val14 = 7;
                                    }
                                    if (!(func_801BB934(9, 0xA, val14, 0xA2) & BYTE_MASK)) {
                                        default: /* switch 5 */
                                            val7 = 3;
                                            if ((SP_REF(u8, 0x8u) & 0xF0) == 0xA0) {
                                            block_108:
                                                val9 = 8;
                                            block_109:
                                                return func_801BB7B0(val9) & BYTE_MASK;
                                            }
                                            val0 = val8;
                                            tmp2 = FIELD(u16, g_SpadWork, 0x36u);
                                            if (func_801BB86C(tmp2, (s16)(tmp2 + 1), val0, val0, val7) & BYTE_MASK) {
                                                g_SpadWork->direction_08 = 7U;
                                                return 1;
                                            }
                                            tmp3 = FIELD(u16, g_SpadWork, 0x36u);
                                            if (func_801BB86C(tmp3, (s16)(tmp3 - 1), val0, val0, val7) & BYTE_MASK) {
                                                g_SpadWork->direction_08 = 3U;
                                                return 1;
                                            }
                                        block_114:
                                            return 3;
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                        block_74:
                            return 0;
                    }
                    return 0;
            }
        } else {
            return 3;
        }
    }
}
#else
INCLUDE_ASM(func_801BA678);
#endif
