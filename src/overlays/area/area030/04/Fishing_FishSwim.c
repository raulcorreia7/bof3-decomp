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

    if (FISHING_STATE->step_timer_09 == 0) {
        if (Fishing_LureInRange() & BYTE_MASK) {
            FISHING_STATE->handler_index_01 = 3;
        } else {
            roll = rand();
            if (D_801E3200 == 0) {
                work = FISHING_STATE;
                if (work->bounce_3C.half.key_3E == 0 && !(roll & 0x3) && D_80145E92[0] != 4 && work->cue_index_06 != FISHING_IDLE_CUE) {
                    D_801E3200 = 1;
                    Area_FindSceneRecord(*(u16*)(D_801E2ACA + work->cue_index_06 * sizeof(FishingSceneCue)));
                    if (!(*(u8*)g_Task & ACTOR_FLAG_OFFSCREEN)) {
                        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
                    }
                    FISHING_STATE->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                    FISHING_STATE->state_2A   = 0;
                    FISHING_STATE->counter_48 = 0;
                    Actor_SelectScript(0);
                    FISHING_STATE->handler_index_01++;
                    return;
                }
            }
            if (roll & 0x4) {
                if (roll & 0x8) {
                    FISHING_STATE->counter_08 = (FISHING_STATE->counter_08 + 1) & 0x7;
                } else {
                    FISHING_STATE->counter_08 = (FISHING_STATE->counter_08 - 1) & 0x7;
                }
            }
            func_801E03F8();
            FISHING_STATE->state_2A = D_801E2331[FISHING_STATE->counter_08 * 2];
            Actor_RequestScript(D_801E2330[FISHING_STATE->counter_08 * 2]);
            turn = Area_SampleHeight(FISHING_STATE->motion_34.unk_34 + FISHING_STATE->pos_x_0C * 0x10, FISHING_STATE->y_38.pos_y + FISHING_STATE->cursor_10 * 0x10);
            work = FISHING_STATE;
            if (work->bounce_3C.half.key_3E < turn) {
                work->step_14 = (turn - work->bounce_3C.half.key_3E) / 16;
            } else {
                work->step_14 = 0;
                if (roll & 0x10) {
                    if (roll & 0x20) {
                        if (work->bounce_3C.half.key_3E != 0 && -(D_801E2AD2[work->cue_index_06 * sizeof(FishingSceneCue)] << 8) >= work->bounce_3C.half.key_3E + 0x20) {
                            work->step_14 = 2;
                        }
                    } else {
                        delta = work->bounce_3C.half.key_3E - 0x20;
                        if (delta >= turn && delta >= -((D_801E2AD2[work->cue_index_06 * sizeof(FishingSceneCue)] + 1) << 8)) {
                            work->step_14 = -2;
                        }
                    }
                }
            }
            if (roll & 0x40) {
                FISHING_STATE->pos_x_0C  = 0;
                FISHING_STATE->cursor_10 = 0;
                FISHING_STATE->step_14   = 0;
            }
            FISHING_STATE->step_timer_09 = 0x10;
        }
    }
    Fishing_MoveFish();
    Actor_StepAnimLoop();
}
