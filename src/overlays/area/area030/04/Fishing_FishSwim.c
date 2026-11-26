#include "area030_04.h"

/* The cue the actor plays when it enters its idle roll. */
#define FISHING_IDLE_CUE 0x16

/* Runs the area-030 actor AI: rolls the idle action, steps the animation, steers the actor toward its target
 * and fires the attack when aligned. */
/* func_801DE82C */
MATCH void Fishing_FishSwim(void) {
    FishingState* work;
    u8            roll; /* random bits; only the low seven are tested */
    s32           delta;
    s16           turn;

    if (TASK(FishingState)->timer == 0) {
        if (Fishing_LureInRange() & BYTE_MASK) {
            TASK(FishingState)->handler_index = 3;
        } else {
            roll = rand();
            if (D_801E3200 == 0) {
                work = TASK(FishingState);
                if (work->bounce.half.key == 0 && !(roll & 0x3) && D_80145E92[0] != 4 && work->cue_index != FISHING_IDLE_CUE) {
                    D_801E3200 = 1;
                    Area_SceneSelectRecord(*(u16*)(D_801E2ACA + work->cue_index * sizeof(FishingSceneCue)));
                    if (!(*TASK(u8) & ACTOR_FLAG_OFFSCREEN)) {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
                    }
                    TASK(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                    TASK(FishingState)->state_2A   = 0;
                    TASK(FishingState)->counter_48 = 0;
                    Script_Select(0);
                    TASK(FishingState)->handler_index++;
                    return;
                }
            }
            if (roll & 0x4) {
                if (roll & 0x8) {
                    TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 + 1) & 0x7;
                } else {
                    TASK(FishingState)->counter_08 = (TASK(FishingState)->counter_08 - 1) & 0x7;
                }
            }
            func_801E03F8();
            TASK(FishingState)->state_2A = D_801E2330[TASK(FishingState)->counter_08][1];
            Script_Request(D_801E2330[TASK(FishingState)->counter_08][0]);
            turn = Area_HeightSample(TASK(FishingState)->motion.unk_34 + TASK(FishingState)->pos_x * 0x10, TASK(FishingState)->y_38.pos_y + TASK(FishingState)->cursor_10 * 0x10);
            work = TASK(FishingState);
            if (work->bounce.half.key < turn) {
                work->bounce_speed = (turn - work->bounce.half.key) / 16;
            } else {
                work->bounce_speed = 0;
                if (roll & 0x10) {
                    if (roll & 0x20) {
                        if (work->bounce.half.key != 0 && -(D_801E2AD2[work->cue_index * sizeof(FishingSceneCue)] << 8) >= work->bounce.half.key + 0x20) {
                            work->bounce_speed = 2;
                        }
                    } else {
                        delta = work->bounce.half.key - 0x20;
                        if (delta >= turn && delta >= -((D_801E2AD2[work->cue_index * sizeof(FishingSceneCue)] + 1) << 8)) {
                            work->bounce_speed = -2;
                        }
                    }
                }
            }
            if (roll & 0x40) {
                TASK(FishingState)->pos_x        = 0;
                TASK(FishingState)->cursor_10    = 0;
                TASK(FishingState)->bounce_speed = 0;
            }
            TASK(FishingState)->timer = 0x10;
        }
    }
    Fishing_MoveFish();
    Script_AnimStepLoop();
}
