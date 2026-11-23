#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801BCD60(s32 target_x, s32 target_y) {
    s8     direction;
    s16    val0;
    s32    tmp0;
    s32    tmp1;
    s32    tmp2;
    s32    tmp3;
    s32    tmp4;
    s32    tmp5;
    s32    tmp6;
    s32    tmp7;
    s32    val1;
    s32    val2;
    s32    val3;
    s32    val4;
    s32    val5;
    s32    val6;
    s32    val7;
    s32    val8;
    s32    val9;
    s32    val10;
    s32    val11;
    s32    val12;
    Actor* tmp8;
    Actor* tmp9;
    Actor* tmp10;
    Actor* tmp11;
    Actor* tmp12;
    Actor* tmp13;
    Actor* tmp14;
    Actor* tmp15;
    Actor* tmp16;
    Actor* tmp18;
    Actor* tmp19;
    Actor* tmp20;
    Actor* tmp21;
    Actor* tmp22;
    Actor* tmp23;

    tmp8 = g_Task;
    if ((tmp8->header.flags & 0x80) && !((g_GameFlags | g_AreaWalkFlags) & BIT(0)) && !(g_Game.members[0].status.field.flags.value & 1)) {
        val9  = tmp8->pos.x.fixed;
        val2  = tmp8->pos.y.fixed;
        tmp6  = val9 - target_x;
        val12 = tmp6;
        if (tmp6 < 0) {
            val12 = -val12;
        }
        tmp7 = val2 - target_y;
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
        val0  = Area_HeightRead(tmp15->pos.x.fixed, tmp15->pos.y.fixed);
        val0 <<= 0x10;
        val0 = (s16)(val0 >> 0x10);
        val0 -= Area_HeightRead(target_x, target_y);
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
            func_801BD290(target_x, target_y, &direction);
            tmp0               = (u8)direction * 8;
            tmp16              = g_Task;
            tmp16->pos.x.fixed = (s32)(val9 + (((s32*)g_FacingSteps)[tmp0] * 2 * val6));
            tmp3               = val2 + (*(g_FacingStepY + tmp0) * 2 * val6);
            tmp16->pos.y.fixed = tmp3;
            val0               = Area_HeightReadStep(tmp16->pos.x.fixed, tmp3, (u8)direction);
            if (Game_TestPlacement(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, val0) & 0xFF) {
                val0 = 1;
                tmp1 = val7 - 1;
                val5 = TASK(Actor)->pos.x.fixed;
                if (tmp1 > 1) {
                    val8 = tmp1;
                    val4 = val5 + TO_COORD(-1);
                    val3 = val5 + TO_COORD(1);
                loop_21:
                    tmp10              = g_Task;
                    tmp10->pos.x.fixed = val3;
                    tmp18              = g_Task;
                    if (Game_TestPlacement(tmp18->pos.x.fixed, tmp18->pos.y.fixed, tmp18->voice_flags.scene_flag, Area_HeightRead(val3, tmp10->pos.y.fixed)) & 0xFF) {
                        tmp11              = g_Task;
                        tmp11->pos.x.fixed = val4;
                        tmp19              = g_Task;
                        if (Game_TestPlacement(tmp19->pos.x.fixed, tmp19->pos.y.fixed, tmp19->voice_flags.scene_flag, Area_HeightRead(val4, tmp11->pos.y.fixed)) & 0xFF) {
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
                    tmp20              = g_Task;
                    tmp2               = val7 - 1;
                    tmp4               = tmp20->pos.y.fixed;
                    tmp20->pos.x.fixed = val5;
                    if (val0 < tmp2) {
                        val5 = tmp2;
                        val4 = tmp4 + TO_COORD(-1);
                        val3 = tmp4 + TO_COORD(1);
                    loop_27:
                        tmp12              = g_Task;
                        tmp12->pos.y.fixed = val3;
                        tmp21              = g_Task;
                        if (Game_TestPlacement(tmp21->pos.x.fixed, tmp21->pos.y.fixed, tmp21->voice_flags.scene_flag, Area_HeightRead(tmp12->pos.x.fixed, val3)) & 0xFF) {
                            tmp13              = g_Task;
                            tmp13->pos.y.fixed = val4;
                            tmp22              = g_Task;
                            if (Game_TestPlacement(tmp22->pos.x.fixed, tmp22->pos.y.fixed, tmp22->voice_flags.scene_flag, Area_HeightRead(tmp13->pos.x.fixed, val4)) & 0xFF) {
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
            val10 = tmp9->pos.x.fixed - g_Game.members[0].pos.x.fixed;
            val10 = ABS(val10);
            if (val10 <= TO_COORD(6)) {
                val11 = tmp9->pos.y.fixed - g_Game.members[0].pos.y.fixed;
                val11 = ABS(val11);
                if (val11 > TO_COORD(6)) {
                    goto block_39; /* retail branch */
                }
                tmp9->pos.x.fixed = val9;
                tmp9->pos.y.fixed = val2;
            } else {
            block_39:
                if (Area_GetWidth(tmp9->pos.x.part.integer, tmp9->pos.y.part.integer) & BYTE_MASK) {
                    g_GameState->status.field.flags.unsigned_value = (u8)(g_GameState->status.field.flags.unsigned_value & 0xFE);
                    TASK(Actor)->draw_layer                        = (u8)g_AreaDrawMode;
                    TASK(Actor)->direction                         = (u8)direction;
                } else {
                    goto block_41; /* retail branch */
                }
            }
        } else {
        block_41:
            tmp14              = g_Task;
            tmp14->pos.x.fixed = val9;
            tmp14->pos.y.fixed = val2;
        }
        tmp23                         = g_Task;
        tmp23->pos.x.fixed            = (s32)(tmp23->pos.x.fixed & ~0x7FFF);
        tmp5                          = tmp23->pos.y.fixed & ~0x7FFF;
        tmp23->pos.y.fixed            = tmp5;
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(tmp23->pos.x.fixed, tmp5);
    }
}
#else
INCLUDE_ASM(func_801BCD60);
#endif
