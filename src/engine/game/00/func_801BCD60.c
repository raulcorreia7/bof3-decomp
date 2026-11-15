#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801BCD60(s32 target_x, s32 target_y) {
    s8    stack_10;
    s32   stack_18;
    s32   stack_20;
    s16   val0;
    s32   tmp0;
    s32   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
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
    s32   val11;
    s32   val12;
    void* tmp8;
    void* tmp9;
    void* tmp10;
    void* tmp11;
    void* tmp12;
    void* tmp13;
    void* tmp14;
    void* tmp15;
    void* tmp16;
    void* tmp17;
    void* tmp18;
    void* tmp19;
    void* tmp20;
    void* tmp21;
    void* tmp22;
    void* tmp23;

    stack_20 = target_y;
    tmp8     = g_Task;
    stack_18 = target_x;
    if ((*(u8*)(tmp8) & 0x80) && !((g_Game.flags | g_Game.walk_flags) & BIT(0)) && !(D_80145FBC & 1)) {
        val9  = FIELD(s32, tmp8, 0x34u);
        val2  = FIELD(s32, tmp8, 0x38u);
        tmp6  = val9 - target_x;
        val12 = tmp6;
        if (tmp6 < 0) {
            val12 = -val12;
        }
        tmp7 = val2 - stack_20;
        val1 = tmp7;
        if (tmp7 < 0) {
            val1 = -val1;
        }
        val12 = MAX(val12, val1);
        if (val12 > 0xFFFFF) {
            val3 = ((s32)(val12 + TO_COORD(-15)) >> 0x10) + 1;
        } else {
            val3 = 1;
        }
        tmp15 = g_Task;
        val0  = Area_ReadHeight(FIELD(s32, tmp15, 0x34u), FIELD(s32, tmp15, 0x38u));
        val0 <<= 0x10;
        val0 = (s16)(val0 >> 0x10);
        val0 -= Area_ReadHeight(stack_18, stack_20);
        val0 = ABS(val0);
        val0 = (s16)(val0 >> 8);
        val3 -= val0;
        val6 = val3;
        if (val3 <= 0) {
            val3 = 1;
            val6 = 1;
        }
        if (val6 > 0) {
            val7 = 0;
        loop_18:
            func_801BD290(stack_18, stack_20, &stack_10);
            tmp0                     = (u8)stack_10 * 8;
            tmp16                    = g_Task;
            FIELD(s32, tmp16, 0x34u) = (s32)(val9 + (((s32*)g_FacingSteps)[tmp0] * 2 * val6));
            tmp3                     = val2 + (*(g_FacingStepY + tmp0) * 2 * val6);
            FIELD(s32, tmp16, 0x38u) = tmp3;
            tmp17                    = g_Task;
            val0                     = 1;
            if (func_801C3E40(FIELD(s32, tmp17, 0x34u), FIELD(s32, tmp17, 0x38u), FIELD(u8, tmp17, 0x70u), Area_ReadStepHeight(FIELD(s32, tmp16, 0x34u), tmp3, (u8)stack_10)) & 0xFF) {
                tmp1 = val7 - 1;
                val5 = g_Task->pos.x.fixed;
                if (tmp1 > 1) {
                    val8 = tmp1;
                    val4 = val5 + TO_COORD(-1);
                    val3 = val5 + TO_COORD(1);
                loop_21:
                    tmp10                    = g_Task;
                    FIELD(s32, tmp10, 0x34u) = val3;
                    tmp18                    = g_Task;
                    if (func_801C3E40(FIELD(s32, tmp18, 0x34u), FIELD(s32, tmp18, 0x38u), FIELD(u8, tmp18, 0x70u), Area_ReadHeight(val3, FIELD(s32, tmp10, 0x38u))) & 0xFF) {
                        tmp11                    = g_Task;
                        FIELD(s32, tmp11, 0x34u) = val4;
                        tmp19                    = g_Task;
                        if (func_801C3E40(FIELD(s32, tmp19, 0x34u), FIELD(s32, tmp19, 0x38u), FIELD(u8, tmp19, 0x70u), Area_ReadHeight(val4, FIELD(s32, tmp11, 0x38u))) & 0xFF) {
                            val4 += TO_COORD(-1);
                            val3 += TO_COORD(1);
                            val0 += 1;
                            if (val0 < val8) {
                                goto loop_21; /* retail branch */
                            }
                        }
                    }
                    val0 = 1;
                    if (val0 >= (val7 - 1)) {
                        goto block_25; /* retail branch */
                    }
                } else {
                block_25:
                    tmp20                    = g_Task;
                    tmp2                     = val7 - 1;
                    tmp4                     = FIELD(s32, tmp20, 0x38u);
                    FIELD(s32, tmp20, 0x34u) = val5;
                    if (val0 < tmp2) {
                        val5 = tmp2;
                        val4 = tmp4 + TO_COORD(-1);
                        val3 = tmp4 + TO_COORD(1);
                    loop_27:
                        tmp12                    = g_Task;
                        FIELD(s32, tmp12, 0x38u) = val3;
                        tmp21                    = g_Task;
                        if (func_801C3E40(FIELD(s32, tmp21, 0x34u), FIELD(s32, tmp21, 0x38u), FIELD(u8, tmp21, 0x70u), Area_ReadHeight(FIELD(s32, tmp12, 0x34u), val3)) & 0xFF) {
                            tmp13                    = g_Task;
                            FIELD(s32, tmp13, 0x38u) = val4;
                            tmp22                    = g_Task;
                            if (func_801C3E40(FIELD(s32, tmp22, 0x34u), FIELD(s32, tmp22, 0x38u), FIELD(u8, tmp22, 0x70u), Area_ReadHeight(FIELD(s32, tmp13, 0x34u), val4)) & 0xFF) {
                                val4 += TO_COORD(-1);
                                val3 += TO_COORD(1);
                                val0 += 1;
                                if (val0 < val5) {
                                    goto loop_27; /* retail branch */
                                }
                            }
                        }
                        if (val0 >= (val7 - 1)) {
                            goto block_31; /* retail branch */
                        }
                    } else {
                    block_31:
                        val6 -= 1;
                        val7 += 1;
                        if (val6 > 0) {
                            goto loop_18; /* retail branch */
                        }
                    }
                }
            }
        }
        if (val6 != 0) {
            tmp9  = g_Task;
            val10 = FIELD(s32, tmp9, 0x34u) - D_80145EC4;
            val10 = ABS(val10);
            if (val10 <= TO_COORD(6)) {
                val11 = FIELD(s32, tmp9, 0x38u) - D_80145EC8;
                val11 = ABS(val11);
                if (val11 > TO_COORD(6)) {
                    goto block_39; /* retail branch */
                }
                FIELD(s32, tmp9, 0x34u) = val9;
                FIELD(s32, tmp9, 0x38u) = val2;
            } else {
            block_39:
                if (Area_GetWidth(FIELD(s16, tmp9, 0x36u), FIELD(s16, tmp9, 0x3Au)) & BYTE_MASK) {
                    g_Game.current->status.field.flags_12C.u8_value = (u8)(g_Game.current->status.field.flags_12C.u8_value & 0xFE);
                    g_Task->unk_29                                  = (u8)g_AreaDrawMode;
                    g_Task->direction_08                            = (u8)stack_10;
                } else {
                    goto block_41; /* retail branch */
                }
            }
        } else {
        block_41:
            tmp14                    = g_Task;
            FIELD(s32, tmp14, 0x34u) = val9;
            FIELD(s32, tmp14, 0x38u) = val2;
        }
        tmp23                    = g_Task;
        FIELD(s32, tmp23, 0x34u) = (s32)(FIELD(s32, tmp23, 0x34u) & ~0x7FFF);
        tmp5                     = FIELD(s32, tmp23, 0x38u) & ~0x7FFF;
        FIELD(s32, tmp23, 0x38u) = tmp5;
        COORD_INT(g_Task->pos.z) = Area_ReadHeight(FIELD(s32, tmp23, 0x34u), tmp5);
    }
}
#else
INCLUDE_ASM(func_801BCD60);
#endif
