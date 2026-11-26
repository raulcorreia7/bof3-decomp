#include "area030_04.h"

/* The fish's reaction to the lure: faces the spawn point, rolls the swim sway,
 * and either hooks the fish or re-rolls the lure's swim. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DECDC(void) {
    s16 height;
    s32 dx;
    s32 dy;
    s32 roll;
    s8  size;
    s32 lure;
    u8* row;

    if (TASK(FishingState)->timer == 0) {
        if (!(Fishing_LureInRange() & BYTE_MASK)) {
            TASK(FishingState)->handler_index = 1;
        } else {
            roll = rand();
            dx   = g_SpawnedActors[0].pos.x.fixed - TASK(FishingState)->motion.unk_34;
            dy   = g_SpawnedActors[0].pos.y.fixed - TASK(FishingState)->y_38.pos_y;
            if (dx < 0 && dy < 0) {
                TASK(FishingState)->counter_08 = 0;
            } else if (dx == 0 && dy < 0) {
                TASK(FishingState)->counter_08 = 1;
            } else if (dx > 0 && dy < 0) {
                TASK(FishingState)->counter_08 = 2;
            } else if (dx > 0 && dy == 0) {
                TASK(FishingState)->counter_08 = 3;
            } else if (dx > 0 && dy > 0) {
                TASK(FishingState)->counter_08 = 4;
            } else if (dx == 0 && dy > 0) {
                TASK(FishingState)->counter_08 = 5;
            } else if (dx < 0 && dy > 0) {
                TASK(FishingState)->counter_08 = 6;
            } else if (dx < 0 && dy == 0) {
                TASK(FishingState)->counter_08 = 7;
            }

            lure = g_FishingLureRow->unk_0E & 0xF;
            row  = FISHING_ENTRY(TASK(FishingState)->cue_index)->pad_04;
            size = g_SpawnedActors[0].unk_07 - row[lure];
            size = (size < -1) ? -1 : (size < 4) ? size : 3;

            switch ((s8)(size + 1)) {
                case 0:
                    TASK(FishingState)->counter_08 ^= 4;
                    if (roll & 0x1) {
                        if (roll & 0x2) {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 + 1) & 0x7;
                        } else {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 - 1) & 0x7;
                        }
                    }
                    break;
                case 1:
                    if (roll & 0xE0) {
                        if (roll & 0x8) {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 + (roll & 0x3)) & 0x7;
                        } else {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 - (roll & 0x3)) & 0x7;
                        }
                    }
                    break;
                case 2:
                    if (!(roll & 0xC0)) {
                        if (roll & 0x8) {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 + (roll & 0x3)) & 0x7;
                        } else {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 - (roll & 0x3)) & 0x7;
                        }
                    }
                    break;
                case 3:
                    if (!(roll & 0xC0)) {
                        if (roll & 0x8) {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 + 1) & 0x7;
                        } else {
                            TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 - 1) & 0x7;
                        }
                    }
                    break;
                case 4:
                    break;
            }

            func_801E03F8();
            height = Area_HeightSample(TASK(FishingState)->motion.unk_34 + TASK(FishingState)->pos_x * 0x10, TASK(FishingState)->y_38.pos_y + TASK(FishingState)->cursor_10 * 0x10);
            if (TASK(FishingState)->bounce.half.key < height) {
                TASK(FishingState)->bounce_speed = (height - TASK(FishingState)->bounce.half.key) / 16;
            } else {
                TASK(FishingState)->bounce_speed = 0;
                if (COORD_INT(g_SpawnedActors[0].pos.z) < TASK(FishingState)->bounce.half.key) {
                    TASK(FishingState)->bounce_speed = -2;
                } else if (TASK(FishingState)->bounce.half.key < COORD_INT(g_SpawnedActors[0].pos.z)) {
                    TASK(FishingState)->bounce_speed = 2;
                }
            }

            TASK(FishingState)->state_2A = D_801E2331[TASK(FishingState)->counter_08 * 2];
            Script_Request(D_801E2330[TASK(FishingState)->counter_08 * 2]);

            if ((func_801E0770() & BYTE_MASK) && (D_801E2AD4[TASK(FishingState)->cue_index][0] > (rand() & 0xF) || (g_FishingLureRow->unk_0E & 0x80)) &&
                (s8)D_801E2ACC[TASK(FishingState)->cue_index][lure = g_FishingLureRow->unk_0E & 0xF] != 9) {
                g_FishingHookedFish              = TASK(Actor)->unk_05;
                D_80145E92[0]                    = 4;
                D_80145E93[0]                    = 0;
                g_SpawnedActors[0].header.mode   = 5;
                g_SpawnedActors[0].vx            = 0;
                g_SpawnedActors[0].selection     = 0;
                g_SpawnedActors[0].unk_14        = 0;
                TASK(FishingState)->pos_x        = 0;
                TASK(FishingState)->cursor_10    = 0;
                TASK(FishingState)->bounce_speed = 0;
                TASK(FishingState)->timer        = 0;
                TASK(FishingState)->step_index   = 0;
                TASK(FishingState)->saved_index  = 0;
                TASK(FishingState)->handler_index++;
                TASK(FishingState)->counter_08 = 1;
                TASK(FishingState)->state_2A   = D_801E2331[TASK(FishingState)->counter_08 << 1];
                Script_Request(D_801E2330[TASK(FishingState)->counter_08 << 1]);
                Script_AnimStepLoop();
                return;
            }

            TASK(FishingState)->timer = 0x10;
            if (size == 3 && (rand() & 0x3) == 0) {
                FishingState* work = TASK(FishingState);
                work->timer        = 8;
                work->pos_x        = work->pos_x << 1;
                work->cursor_10    = work->cursor_10 << 1;
                work->bounce_speed = work->bounce_speed << 1;
            }
        }
    }
    Fishing_MoveFish();
    Script_AnimStepLoop();
}
#else
INCLUDE_ASM(func_801DECDC);
#endif
