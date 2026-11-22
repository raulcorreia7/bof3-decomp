#include "area030_04.h"

/* The fish's reaction to the lure: faces the spawn point, rolls the swim sway,
 * and either hooks the fish or re-rolls the lure's swim. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DECDC(void) {
    FishingState* work;
    s16           height;
    s16           key;
    s32           dx;
    s32           dy;
    u8            roll;
    s8            size;

    work = TASK(FishingState);
    if (work->timer == 0) {
        if (!(Fishing_LureInRange() & BYTE_MASK)) {
            work->handler_index = 1;
        } else {
            roll = rand();
            dx   = g_SpawnedActors[0].pos.x.fixed - work->motion.unk_34;
            dy   = g_SpawnedActors[0].pos.y.fixed - work->y_38.pos_y;
            if (dx < 0) {
                if (dy < 0) {
                    work->counter_08 = 0;
                } else if (dy > 0) {
                    work->counter_08 = 6;
                } else {
                    work->counter_08 = 7;
                }
            } else if (dx > 0) {
                if (dy < 0) {
                    work->counter_08 = 2;
                } else if (dy > 0) {
                    work->counter_08 = 4;
                } else {
                    work->counter_08 = 3;
                }
            } else if (dy < 0) {
                work->counter_08 = 1;
            } else if (dy > 0) {
                work->counter_08 = 5;
            }

            /* 9 marks the end of the species' lure row. */
            size = g_SpawnedActors[0].unk_07 - D_801E2ACC[work->cue_index * sizeof(FishingSceneCue) + (g_FishingLureRow->unk_0E & 0xF)];
            if (size < -1) {
                size = -1;
            } else if (size >= 4) {
                size = 3;
            }

            switch (size + 1) {
                case 0:
                    work->counter_08 ^= 4;
                    if (roll & 0x1) {
                        if (roll & 0x2) {
                            work->counter_08 = (work->counter_08 + 1) & 0x7;
                        } else {
                            work->counter_08 = (work->counter_08 - 1) & 0x7;
                        }
                    }
                    break;
                case 1:
                    if (roll & 0xE0) {
                        if (roll & 0x8) {
                            work->counter_08 = (work->counter_08 + (roll & 0x3)) & 0x7;
                        } else {
                            work->counter_08 = (work->counter_08 - (roll & 0x3)) & 0x7;
                        }
                    }
                    break;
                case 2:
                    if (!(roll & 0xC0)) {
                        if (roll & 0x8) {
                            work->counter_08 = (work->counter_08 + (roll & 0x3)) & 0x7;
                        } else {
                            work->counter_08 = (work->counter_08 - (roll & 0x3)) & 0x7;
                        }
                    }
                    break;
                case 3:
                    if (!(roll & 0xC0)) {
                        if (roll & 0x8) {
                            work->counter_08 = (work->counter_08 + 1) & 0x7;
                        } else {
                            work->counter_08 = (work->counter_08 - 1) & 0x7;
                        }
                    }
                    break;
                default:
                    break;
            }

            func_801E03F8();
            height = Area_HeightSample(work->motion.unk_34 + work->pos_x * 0x10, work->y_38.pos_y + work->cursor_10 * 0x10);
            key    = work->bounce.half.key;
            if (key < height) {
                work->bounce_speed = (height - key) / 16;
            } else {
                work->bounce_speed = 0;
                if (COORD_INT(g_SpawnedActors[0].pos.z) < key) {
                    work->bounce_speed = -2;
                } else if (key < COORD_INT(g_SpawnedActors[0].pos.z)) {
                    work->bounce_speed = 2;
                }
            }

            work->state_2A = D_801E2331[work->counter_08 * 2];
            Script_Request(D_801E2330[work->counter_08 * 2]);

            if (func_801E0770() != 0 && ((rand() & 0xF) < D_801E2AD4[work->cue_index * sizeof(FishingSceneCue)] || (g_FishingLureRow->unk_0E & 0x80)) &&
                D_801E2ACC[work->cue_index * sizeof(FishingSceneCue) + (g_FishingLureRow->unk_0E & 0xF)] != 9) {
                g_FishingHookedFish            = TASK(Actor)->unk_05;
                D_80145E92[0]                  = 4;
                D_80145E93[0]                  = 0;
                g_SpawnedActors[0].header.mode = 5;
                g_SpawnedActors[0].vx          = 0;
                g_SpawnedActors[0].selection   = 0;
                g_SpawnedActors[0].unk_14      = 0;
                work->timer                    = 0;
                work->motion.unk_34            = 0;
                work->cursor_10                = 0;
                work->bounce_speed             = 0;
                work->step_index               = 0;
                work->saved_index              = 0;
                work->handler_index += 1;
                work->counter_08 = 1;
                work->state_2A   = D_801E2331[work->counter_08 * 2];
                Script_Request(D_801E2330[work->counter_08 * 2]);
                Script_AnimStepLoop();
                return;
            }

            work->timer = 0x10;
            if (size == 3 && (rand() & 0x3) == 0) {
                work->timer         = 8;
                work->motion.unk_34 = work->motion.unk_34 << 1;
                work->bounce_speed  = work->bounce_speed << 1;
                work->cursor_10     = work->cursor_10 << 1;
            }
        }
    }
    Fishing_MoveFish();
    Script_AnimStepLoop();
}
#else
INCLUDE_ASM(func_801DECDC);
#endif
