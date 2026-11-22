#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801B4D7C(u8 wanted_code) {
    s32*   val0;
    s16    tmp0;
    s16    tmp1;
    s32    tmp2;
    s32    tmp3;
    s32    tmp4;
    s32    tmp5;
    s32    tmp6;
    s32    tmp7;
    s32    tmp8;
    s32    tmp9;
    s32    val1;
    s32    val2;
    s32    val3;
    s8     tmp10;
    s8     tmp11;
    u16    val4;
    u16    val5;
    u8     tmp12;
    u8     tmp13;
    u8     tmp14;
    u8     tmp15;
    u8     tmp16;
    u8     tmp17;
    u8     val6;
    u8     val7;
    Actor* tmp18;
    Actor* tmp19;
    Actor* tmp20;
    Actor* tmp21;
    Actor* tmp22;
    Actor* tmp23;
    Actor* tmp24;
    Actor* tmp25;
    Actor* tmp26;
    Actor* tmp27;
    Actor* tmp28;
    Actor* tmp29;
    void*  val8;

    tmp28 = g_Task;
    val6  = wanted_code;
    if ((tmp28->pos.x.part.fraction != 0) || (val7 = 0, (tmp28->pos.y.part.fraction != 0))) {
        tmp26 = g_Task;
        tmp10 = *(D_80181B00 + (tmp26->direction * 2));
        tmp0  = tmp26->pos.x.part.integer;
        val5  = tmp0 + tmp10;
        if (tmp10 == 1) {
            val5 = tmp0 + 2;
        }
        tmp27 = g_Task;
        tmp11 = *(D_80181B01 + (tmp27->direction * 2));
        tmp1  = tmp27->pos.y.part.integer;
        val4  = tmp1 + tmp11;
        if (tmp11 == 1) {
            val4 = tmp1 + 2;
        }
        tmp29 = g_Task;
        val1  = 0;
        if (tmp29->pos.x.part.fraction != 0) {
            val2 = 1;
            if (tmp29->pos.y.part.fraction != 0) {
                val0                         = &g_ScratchPad;
                val8                         = (void*)5;
                GAME_ENTITY_ENTRY_DATA       = val4;
                g_ScratchPad.cells.halves[0] = tmp29->pos.x.part.integer;
            loop_9:
                if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == (val6 & BYTE_MASK)) {
                    tmp25 = g_Task;
                    tmp17 = tmp25->direction;
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
                        tmp25->direction = 1U;
                    } else {
                        tmp25->direction = 5U;
                    }
                    goto block_32; /* retail branch */
                }
            block_18:
                val1 += 1;
                g_ScratchPad.cells.halves[0] = (u16)(g_ScratchPad.cells.halves[0] + 1);
                val3                         = 7;
                if (val1 >= 2) {
                    val1                         = 0;
                    val2                         = 3;
                    val0                         = &g_ScratchPad;
                    g_ScratchPad.cells.halves[0] = val5;
                    val8                         = &g_ScratchPad + 2;
                    SP_REF(void*, 0x2)           = COORD_INT(TASK(Actor)->pos.y);
                loop_20:
                    if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == (val6 & BYTE_MASK)) {
                        tmp18 = g_Task;
                        tmp12 = tmp18->direction;
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
                            tmp18->direction = 7U;
                        } else {
                            tmp18->direction = 3U;
                        }
                        goto block_32; /* retail branch */
                    }
                block_29:
                    val1 += 1;
                    g_ScratchPad.cells.halves[1] = (s16)(g_ScratchPad.cells.halves[1] + 1);
                    if (val1 >= 2) {
                        val1 = val6 & BYTE_MASK;
                        val7 = 1;
                        if (!(func_801B4BE4((TASK(Actor)->direction + 2) & 7, (u8)val1) & BYTE_MASK)) {
                            val7 = 0;
                            if (func_801B4BE4((TASK(Actor)->direction - 2) & 7, (u8)val1) & BYTE_MASK) {
                                goto block_32; /* retail branch */
                            }
                        }
                        return val7;
                    }
                    goto loop_20; /* retail branch */
                }
                goto loop_9; /* retail branch */
            }
            val3                         = 7;
            val2                         = 3;
            val0                         = &g_ScratchPad;
            g_ScratchPad.cells.halves[0] = val5;
            val8                         = &g_ScratchPad + 2;
            SP_REF(void*, 0x2)           = (u16)(tmp29->pos.y.part.integer - 1);
        loop_58:
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == (val6 & BYTE_MASK)) {
                tmp22 = g_Task;
                tmp15 = tmp22->direction;
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
                    tmp22->direction = 7U;
                } else {
                    tmp22->direction = 3U;
                }
                goto block_32; /* retail branch */
            }
        block_67:
            val1 += 1;
            g_ScratchPad.cells.halves[1] = (s16)(g_ScratchPad.cells.halves[1] + 1);
            if (val1 >= 3) {
                tmp23 = g_Task;
                tmp16 = tmp23->direction;
                if ((tmp16 == 1) || (val7 = 0, (tmp16 == 5))) {
                    val1                         = 0;
                    val0                         = &g_ScratchPad;
                    g_ScratchPad.cells.halves[0] = (u16)(tmp23->pos.x.part.integer - 1);
                    val8                         = (void*)(val6 & BYTE_MASK);
                    SP_REF(void*, 0x2)           = (u16)(tmp23->pos.y.part.integer - 1);
                loop_71:
                    val1 += 1;
                    if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != val8) {
                        g_ScratchPad.cells.halves[1] = (s16)(g_ScratchPad.cells.halves[1] + 1);
                        if (val1 >= 3) {
                            val1                         = 0;
                            tmp24                        = g_Task;
                            val0                         = &g_ScratchPad;
                            g_ScratchPad.cells.halves[0] = (u16)(tmp24->pos.x.part.integer + 2);
                            val8                         = (void*)(val6 & BYTE_MASK);
                            SP_REF(void*, 0x2)           = (u16)(tmp24->pos.y.part.integer - 1);
                        loop_74:
                            val1 += 1;
                            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != val8) {
                                g_ScratchPad.cells.halves[1] = (s16)(g_ScratchPad.cells.halves[1] + 1);
                                val7                         = 0;
                                if (val1 >= 3) {
                                    return val7;
                                }
                                goto loop_74; /* retail branch */
                            }
                            TASK(Actor)->direction = FACING_RIGHT;
                            return 1U;
                        }
                        goto loop_71; /* retail branch */
                    }
                    TASK(Actor)->direction = FACING_LEFT;
                    return 1U;
                }
                return val7;
            }
            goto loop_58; /* retail branch */
        }
        val0                         = &g_ScratchPad;
        val2                         = 1;
        val8                         = (void*)5;
        SP_REF(void*, 0x2)           = val4;
        g_ScratchPad.cells.halves[0] = (u16)(tmp29->pos.x.part.integer - 1);
    loop_34:
        if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == (val6 & BYTE_MASK)) {
            tmp19 = g_Task;
            tmp13 = tmp19->direction;
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
                tmp19->direction = 1U;
            } else {
                tmp19->direction = 5U;
            }
        block_32:
            return 1U;
        }
    block_43:
        val1 += 1;
        g_ScratchPad.cells.halves[0] = (u16)(g_ScratchPad.cells.halves[0] + 1);
        if (val1 >= 3) {
            tmp20 = g_Task;
            tmp14 = tmp20->direction;
            if ((tmp14 == 7) || (val7 = 0, (tmp14 == 3))) {
                val1                         = 0;
                val0                         = &g_ScratchPad;
                g_ScratchPad.cells.halves[0] = (u16)(tmp20->pos.x.part.integer - 1);
                val8                         = (void*)(val6 & BYTE_MASK);
                SP_REF(void*, 0x2)           = (u16)(tmp20->pos.y.part.integer - 1);
            loop_47:
                val1 += 1;
                if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != val8) {
                    g_ScratchPad.cells.halves[0] = (u16)(g_ScratchPad.cells.halves[0] + 1);
                    if (val1 >= 3) {
                        val1                         = 0;
                        tmp21                        = g_Task;
                        val0                         = &g_ScratchPad;
                        g_ScratchPad.cells.halves[0] = (u16)(tmp21->pos.x.part.integer - 1);
                        val8                         = (void*)(val6 & BYTE_MASK);
                        SP_REF(void*, 0x2)           = (u16)(tmp21->pos.y.part.integer + 2);
                    loop_50:
                        val1 += 1;
                        if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != val8) {
                            g_ScratchPad.cells.halves[0] = (u16)(g_ScratchPad.cells.halves[0] + 1);
                            if (val1 >= 3) {
                                return 0U;
                            }
                            goto loop_50; /* retail branch */
                        }
                        TASK(Actor)->direction = FACING_DOWN;
                        return 1U;
                    }
                    goto loop_47; /* retail branch */
                }
                TASK(Actor)->direction = FACING_UP;
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
