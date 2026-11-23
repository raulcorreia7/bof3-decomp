#include "area030_04.h"

/* The hooked fish's fight: reacts to the rod's reel window, rolls the fish's
 * next jerk and walks the depth-and-direction steps that raise or lower the
 * lure against it. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DF334(void) {
    FishingState* work;
    s32           amount;
    s32           grade;
    s32           scaled;
    s32           span;
    s32           value;
    u8            center;
    u8            lower;
    u8            upper;

    work   = TASK(FishingState);
    center = g_SpawnedActors[5].screen_y;
    span   = g_FishingRodRow->reel_cursor_size * 4;
    lower  = center - span - 0xC;
    upper  = center + span + 0xC;
    if (work->y_38.pos_y <= 0x8000) {
        g_SpawnedActors[5].selection   = -7;
        g_SpawnedActors[0].header.mode = 0;
        D_80145E92[0]                  = 6;
        D_80145E93[0]                  = 0;
        work->handler_index += 1;
        return;
    }

    if (work->flag_04 == 3) {
        if (Script_AnimStepLoop() & BYTE_MASK) {
            Area_SceneSelectRecord(FISHING_ENTRY(work->cue_index)->scene_id);
            work->flags |= 0x20;
            work->state_2A = D_801E2331[work->counter_08 * 2];
            Script_Select(D_801E2330[work->counter_08 * 2]);
            work->bounce.half.key = -0x20;
            work->flag_04         = 0;
            work->counter_48      = 2;
            work->cursor_10       = 0;
            g_SpawnedActors[0].header.flags &= ~0x40;
        }
        if (work->flags_58 >= 0x15) {
            work->step_index += work->cursor_10;
            value = (s8)work->step_index;
            if (value < -0x30) {
                value = -0x30;
            } else if (value >= 0x31) {
                value = 0x30;
            }
            work->step_index = value;
        }
        return;
    }

    if (g_SpawnedActors[4].header.mode == 0) {
        if ((s8)upper < (s8)work->step_index) {
            work->saved_index += 1;
            if (work->saved_index >= g_FishingRodRow->snap_left_tension) {
                work->saved_index = 0;
                if (g_SpawnedActors[5].selection < 0 && work->cursor_10 > 0 && (func_801E02D4(upper, 1) & BYTE_MASK)) {
                    g_SpawnedActors[5].selection   = -7;
                    g_SpawnedActors[0].header.mode = 0;
                    D_80145E92[0]                  = 6;
                    D_80145E93[0]                  = 0;
                    work->handler_index += 1;
                    return;
                }
            }
        } else if ((s8)work->step_index < (s8)lower) {
            work->saved_index = 0;
        } else {
            work->saved_index += 1;
            if (work->saved_index >= g_FishingRodRow->snap_right_tension) {
                work->saved_index = 0;
                if (func_801E02D4(lower, 2) & BYTE_MASK) {
                    D_80145E92[0]                  = 7;
                    D_80145E93[0]                  = 0;
                    g_SpawnedActors[0].header.mode = 0;
                    work->handler_index += 1;
                    return;
                }
            }
        }
    }

    if (work->timer != 0) {
        work->timer -= 1;
        value  = (s8)FISHING_ROW->timer_75;
        scaled = FISHING_ROW->ext.fishing.stamina_max << 16;
        if (value > 0) {
            if ((g_FrameCount & 0xF) == 0 && work->cursor_10 >= 0 && (s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 17)) {
                Fishing_FishStaminaAdd(value);
            }
        } else if ((g_FrameCount & 1) != 0) {
            Fishing_FishStaminaAdd(value);
        }
    } else {
        scaled = FISHING_ROW->ext.fishing.stamina_max << 16;
        if ((s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 18)) {
            grade = 3;
        } else if ((s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 17)) {
            grade = 2;
        } else {
            grade = (s16)FISHING_ROW->ext.fishing.stamina < (scaled >> 18) * 3;
        }

        if ((rand() & 0xF) < D_801E2AB8[work->cue_index * sizeof(FishingSceneCue) + grade * 4]) {
            scaled = FISHING_ROW->ext.fishing.stamina_max << 16;
            if ((s16)FISHING_ROW->ext.fishing.stamina > (scaled >> 20)) {
                work->cursor_10 = (rand() & (D_801E2AD5[work->cue_index * sizeof(FishingSceneCue)] & 0x7)) + 1;
                if ((s8)work->step_index < 0) {
                    work->cursor_10 += rand() & 1;
                }
                if (work->cursor_10 < 0) {
                    work->cursor_10 = 0;
                } else if (work->cursor_10 >= 6) {
                    work->cursor_10 = 5;
                }
                if (g_SpawnedActors[5].selection < 0) {
                    value = (s8)work->step_index - g_SpawnedActors[5].screen_y;
                    if (value < -0x30) {
                        FISHING_ROW->timer_75 = 0xFD;
                    } else if (value < -0x18) {
                        FISHING_ROW->timer_75 = 0xFE;
                    } else {
                        FISHING_ROW->timer_75 = 0xFF;
                    }
                }
            } else {
                work->cursor_10       = 0;
                FISHING_ROW->timer_75 = 0;
            }

            if (D_801E2AD8[work->cue_index * sizeof(FishingSceneCue)] != 0) {
                if (rand() & 1) {
                    if (rand() & 1) {
                        work->pos_x = 0x1000;
                    } else {
                        work->pos_x = -0x1000;
                    }
                } else {
                    work->pos_x = 0;
                }
            } else {
                work->pos_x = 0;
            }
            work->counter_08 = 1;
            work->flag_04    = 0;
        } else if ((rand() & 0xF) < D_801E2AB8[work->cue_index * sizeof(FishingSceneCue) + grade * 4 + 2]) {
            work->pos_x           = 0;
            work->cursor_10       = 0;
            FISHING_ROW->timer_75 = 1;
            work->flag_04         = 1;
        } else if (work->step_index != 0) {
            FISHING_ROW->timer_75 = 0;
            work->cursor_10       = -1;
            work->pos_x           = 0;
            work->flag_04         = 2;
        }
        work->timer = (8 - grade) * ((rand() & 3) + 1);
    }

    work->step_index += work->cursor_10 + work->unk_1C;
    value = (s8)work->step_index;
    if (value < -0x30) {
        value = -0x30;
    } else if (value >= 0x31) {
        value = 0x30;
    }
    work->step_index = value;

    if (g_AreaCameraMoving == 0) {
        g_AreaCameraSpeed = 0;
    }
    if (g_SpawnedActors[5].screen_y < (s8)work->step_index && work->cursor_10 > 0) {
        work->y_38.pos_y = work->y_38.pos_y - 0x1000;
        if (work->bounce.half.key < 0) {
            work->bounce.half.key += 8;
        }
        if (work->y_38.pos_y > 0x150000) {
            g_AreaCameraSpeed   = 0x10;
            g_AreaScrollTargetY = work->y_38.pos_y;
            if (work->y_38.pos_y > 0x3C0000) {
                g_AreaScrollTargetY = 0x3C0000;
            }
        }
        if (work->pos_x < 0) {
            if (work->motion.unk_34 <= 0x60000) {
                work->pos_x = -work->pos_x;
            }
        } else if (work->pos_x > 0) {
            if (work->motion.unk_34 > 0x13FFFF) {
                work->pos_x = -work->pos_x;
            }
        } else {
            work->pos_x = 0;
        }
        work->motion.unk_34 += work->pos_x;
        if (work->pos_x < -0x800) {
            work->counter_08 = 0;
        } else if (work->pos_x < 0x801) {
            work->counter_08 = 1;
        } else {
            work->counter_08 = 2;
        }
    } else if ((s8)work->step_index < g_SpawnedActors[5].screen_y && g_SpawnedActors[5].selection < 0) {
        amount = 0x3E - work->y_38.slot.slot;
        if (amount != 0) {
            work->pos_x = ((0xF0000 - work->motion.unk_34) >> 4) / amount;
            if (work->pos_x < -0x1000) {
                work->pos_x = -0x1000;
            } else if (work->pos_x >= 0x1001) {
                work->pos_x = 0x1000;
            }
        } else {
            work->pos_x = 0;
        }
        work->motion.unk_34 += work->pos_x;
        if (work->bounce.half.key < 0) {
            work->bounce.half.key += 8;
        }
        work->y_38.pos_y += 0x1000;
        if (work->y_38.pos_y > 0x150000) {
            g_AreaCameraSpeed   = 0x10;
            g_AreaScrollTargetY = work->y_38.pos_y;
            if (work->y_38.pos_y > 0x3C0000) {
                g_AreaScrollTargetY = 0x3C0000;
            }
        }
        if (work->flag_04 == 0) {
            work->counter_08 = 1;
        } else {
            work->counter_08 = 5;
        }
    }

    work->state_2A = D_801E2331[work->counter_08 * 2];
    Script_Request(D_801E2330[work->counter_08 * 2]);
    Script_AnimStepLoop();
}
#else
INCLUDE_ASM(func_801DF334);
#endif
