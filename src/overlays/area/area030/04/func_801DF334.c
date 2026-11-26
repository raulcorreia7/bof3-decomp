#include "area030_04.h"

/* The hooked fish's fight: reacts to the rod's reel window, rolls the fish's
 * next jerk and walks the depth-and-direction steps that raise or lower the
 * lure against it. */
#ifdef NON_MATCHING
/* The fish's depth against the reel window, held to -0x30..0x30. */
static inline u8 Fishing_ClampDepth(s8 depth) {
    if (depth < -0x30) {
        return -0x30;
    }
    if (depth > 0x30) {
        return 0x30;
    }
    return depth;
}

NON_MATCHING void func_801DF334(void) {
    s32 amount;
    s32 grade;
    s32 scaled;
    s32 span;
    s32 value;
    u8  center;
    u8  lower;
    u8  upper;
    u8* odds;

    center = g_SpawnedActors[5].screen_y;
    span   = g_FishingRodRow->reel_cursor_size * 4;
    lower  = center - span - 0xC;
    upper  = center + span + 0xC;
    odds   = &D_801E2AB8[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)];
    if (TASK(FishingState)->y_38.pos_y <= 0x8000) {
        g_SpawnedActors[5].selection   = -7;
        g_SpawnedActors[0].header.mode = 0;
        D_80145E92[0]                  = 6;
        D_80145E93[0]                  = 0;
        TASK(FishingState)->handler_index += 1;
        return;
    }

    if (TASK(FishingState)->flag_04 == 3) {
        if (Script_AnimStepLoop() & BYTE_MASK) {
            Area_SceneSelectRecord(FISHING_ENTRY(TASK(FishingState)->cue_index)->scene_id);
            TASK(FishingState)->flags |= 0x20;
            TASK(FishingState)->state_2A = D_801E2331[TASK(FishingState)->counter_08 * 2];
            Script_Select(D_801E2330[TASK(FishingState)->counter_08 * 2]);
            TASK(FishingState)->bounce.half.key = -0x20;
            TASK(FishingState)->flag_04         = 0;
            TASK(FishingState)->counter_48      = 2;
            TASK(FishingState)->cursor_10       = 0;
            g_SpawnedActors[0].header.flags &= ~0x40;
        }
        if (TASK(FishingState)->flags_58 >= 0x15) {
            TASK(FishingState)->step_index += TASK(FishingState)->cursor_10;
            {
                FishingState* work = TASK(FishingState);
                work->step_index   = Fishing_ClampDepth(work->step_index);
            }
        }
        return;
    }

    if (g_SpawnedActors[4].header.mode == 0) {
        if ((s8)upper < (s8)TASK(FishingState)->step_index) {
            TASK(FishingState)->saved_index += 1;
            if (TASK(FishingState)->saved_index >= g_FishingRodRow->snap_left_tension) {
                TASK(FishingState)->saved_index = 0;
                if (g_SpawnedActors[5].selection < 0 && TASK(FishingState)->cursor_10 > 0 && (func_801E02D4(upper, 1) & BYTE_MASK)) {
                    g_SpawnedActors[5].selection   = -7;
                    g_SpawnedActors[0].header.mode = 0;
                    D_80145E92[0]                  = 6;
                    D_80145E93[0]                  = 0;
                    TASK(FishingState)->handler_index += 1;
                    return;
                }
            }
        } else if ((s8)TASK(FishingState)->step_index < (s8)lower) {
            TASK(FishingState)->saved_index += 1;
            if (TASK(FishingState)->saved_index >= g_FishingRodRow->snap_right_tension) {
                TASK(FishingState)->saved_index = 0;
                if (func_801E02D4(lower, 2) & BYTE_MASK) {
                    D_80145E92[0]                  = 7;
                    D_80145E93[0]                  = 0;
                    g_SpawnedActors[0].header.mode = 0;
                    TASK(FishingState)->handler_index += 1;
                    return;
                }
            }
        } else {
            TASK(FishingState)->saved_index = 0;
        }
    }

    if (TASK(FishingState)->timer == 0) {
        scaled = (u16)FISHING_ROW->ext.fishing.stamina_max << 16;
        if ((s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 18)) {
            grade = 3;
        } else if ((s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 17)) {
            grade = 2;
        } else if ((s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 18) * 3) {
            grade = 1;
        } else {
            grade = 0;
        }

        if ((rand() & 0xF) < odds[grade * 4] && TASK(FishingState)->bounce.half.key >= -0x3F && (s8)TASK(FishingState)->step_index > 0) {
            g_SpawnedActors[0].header.flags |= 0x40;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
            Area_SceneSelectRecord(FISHING_ENTRY(TASK(FishingState)->cue_index)->hook_scene_id);
            TASK(FishingState)->flags &= ~0x20;
            TASK(FishingState)->state_2A        = 0;
            TASK(FishingState)->counter_48      = 0;
            TASK(FishingState)->bounce.half.key = 0;
            Script_Select(0);
            TASK(FishingState)->cursor_10 = -3;
            Fishing_FishStaminaAdd(-5);
            TASK(FishingState)->flag_04 = 3;
            return;
        }
        if ((rand() & 0xF) < odds[grade * 4 + 1]) {
            scaled = (u16)FISHING_ROW->ext.fishing.stamina_max << 16;
            if ((s16)FISHING_ROW->ext.fishing.stamina > (scaled >> 20)) {
                TASK(FishingState)->cursor_10 = (rand() & (D_801E2AD5[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)] & 0x7)) + 1;
                if ((s8)TASK(FishingState)->step_index < 0) {
                    TASK(FishingState)->cursor_10 += rand() & 1;
                }
                {
                    FishingState* work = TASK(FishingState);
                    value              = work->cursor_10;
                    amount             = (value < 0) ? 0 : ((value > 5) ? 5 : value);
                    work->cursor_10    = amount;
                }
                if (g_SpawnedActors[5].selection < 0) {
                    value = (s8)TASK(FishingState)->step_index - g_SpawnedActors[5].screen_y;
                    if (value < -0x30) {
                        FISHING_ROW->timer_75 = 0xFD;
                    } else if (value < -0x18) {
                        FISHING_ROW->timer_75 = 0xFE;
                    } else {
                        FISHING_ROW->timer_75 = 0xFF;
                    }
                }
            } else {
                TASK(FishingState)->cursor_10 = 0;
                FISHING_ROW->timer_75         = 0;
            }

            if (D_801E2AD8[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)] != 0) {
                if (rand() & 1) {
                    if (rand() & 1) {
                        TASK(FishingState)->pos_x = 0x1000;
                    } else {
                        TASK(FishingState)->pos_x = -0x1000;
                    }
                } else {
                    TASK(FishingState)->pos_x = 0;
                }
            } else {
                TASK(FishingState)->pos_x = 0;
            }
            TASK(FishingState)->counter_08 = 1;
            TASK(FishingState)->flag_04    = 0;
        } else if ((rand() & 0xF) < odds[grade * 4 + 2]) {
            TASK(FishingState)->pos_x     = 0;
            TASK(FishingState)->cursor_10 = 0;
            FISHING_ROW->timer_75         = 1;
            TASK(FishingState)->flag_04   = 1;
        } else if (TASK(FishingState)->step_index != 0) {
            FISHING_ROW->timer_75         = 0;
            TASK(FishingState)->cursor_10 = -1;
            TASK(FishingState)->pos_x     = 0;
            TASK(FishingState)->flag_04   = 2;
        }
        TASK(FishingState)->timer = (8 - grade) * ((rand() & 3) + 1);
    } else {
        TASK(FishingState)->timer -= 1;
        if ((s8)FISHING_ROW->timer_75 > 0) {
            if ((g_FrameCount & 0xF) == 0 && TASK(FishingState)->cursor_10 >= 0 && (s16)FISHING_ROW->ext.fishing.stamina < ((u16)FISHING_ROW->ext.fishing.stamina_max << 16 >> 17)) {
                Fishing_FishStaminaAdd(FISHING_ROW->timer_75);
            }
        } else if ((g_FrameCount & 1) != 0) {
            Fishing_FishStaminaAdd(FISHING_ROW->timer_75);
        }
    }

    TASK(FishingState)->step_index += TASK(FishingState)->cursor_10 + TASK(FishingState)->unk_1C;
    {
        FishingState* work = TASK(FishingState);
        work->step_index   = Fishing_ClampDepth(work->step_index);
    }

    if (g_AreaCameraMoving == 0) {
        g_AreaCameraSpeed = 0;
    }
    if (g_SpawnedActors[5].screen_y < (s8)TASK(FishingState)->step_index && TASK(FishingState)->cursor_10 > 0) {
        TASK(FishingState)->y_38.pos_y = TASK(FishingState)->y_38.pos_y - 0x1000;
        if (TASK(FishingState)->bounce.half.key < 0) {
            TASK(FishingState)->bounce.half.key += 8;
        }
        value = TASK(FishingState)->y_38.pos_y;
        if (value > 0x150000) {
            g_AreaCameraSpeed   = 0x10;
            g_AreaScrollTargetY = value;
            if (value > 0x3C0000) {
                g_AreaScrollTargetY = 0x3C0000;
            }
        }
        if (TASK(FishingState)->pos_x < 0) {
            if (TASK(FishingState)->motion.unk_34 <= 0x60000) {
                TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x;
            }
        } else if (TASK(FishingState)->pos_x > 0) {
            if (TASK(FishingState)->motion.unk_34 > 0x13FFFF) {
                TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x;
            }
        } else {
            TASK(FishingState)->pos_x = 0;
        }
        TASK(FishingState)->motion.unk_34 += TASK(FishingState)->pos_x;
        if (TASK(FishingState)->pos_x < -0x800) {
            TASK(FishingState)->counter_08 = 0;
        } else if (TASK(FishingState)->pos_x > 0x800) {
            TASK(FishingState)->counter_08 = 2;
        } else {
            TASK(FishingState)->counter_08 = 1;
        }
    } else if ((s8)TASK(FishingState)->step_index < g_SpawnedActors[5].screen_y && g_SpawnedActors[5].selection < 0) {
        FishingState* work = TASK(FishingState);
        amount             = 0x3E - work->y_38.slot.slot;
        scaled             = 0xF0000 - work->motion.unk_34;
        if (amount != 0) {
            value       = (scaled >> 4) / amount;
            work->pos_x = value;
            amount      = (value < -0x1000) ? -0x1000 : ((value > 0x1000) ? 0x1000 : value);
            work->pos_x = amount;
        } else {
            work->pos_x = 0;
        }
        TASK(FishingState)->motion.unk_34 += TASK(FishingState)->pos_x;
        if (TASK(FishingState)->bounce.half.key < 0) {
            TASK(FishingState)->bounce.half.key += 8;
        }
        value                          = TASK(FishingState)->y_38.pos_y + 0x1000;
        TASK(FishingState)->y_38.pos_y = value;
        if (value > 0x150000) {
            g_AreaCameraSpeed   = 0x10;
            g_AreaScrollTargetY = value;
            if (value > 0x3C0000) {
                g_AreaScrollTargetY = 0x3C0000;
            }
        }
        if (TASK(FishingState)->flag_04 == 0) {
            TASK(FishingState)->counter_08 = 1;
        } else {
            TASK(FishingState)->counter_08 = 5;
        }
    }

    TASK(FishingState)->state_2A = D_801E2331[TASK(FishingState)->counter_08 * 2];
    Script_Request(D_801E2330[TASK(FishingState)->counter_08 * 2]);
    Script_AnimStepLoop();
}
#else
INCLUDE_ASM(func_801DF334);
#endif
