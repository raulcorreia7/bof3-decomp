#include "area030_04.h"

/* Advances the work record's motion and bounce timers and selects the walk animation direction. */
/* func_801D2648 */
MATCH void Fishing_LureFloat(void) {
    s32 total;
    s32 step;
    s32 cursor;
    s16 slot;

    if (TASK(FishingState)->step_index != 0) {
        TASK(FishingState)->step_index -= 1;
        if (TASK(FishingState)->step_index == 0 && (s8)g_FishingLureRow->unk_0F < TASK(FishingState)->counter_07) {
            TASK(FishingState)->step_index = g_FishingLureRow->unk_10;
            TASK(FishingState)->counter_07 -= 1;
        }
    }
    TASK(FishingState)->motion.unk_34 += TASK(FishingState)->pos_x;
    TASK(FishingState)->y_38.pos_y += TASK(FishingState)->cursor_10;
    step                              = TASK(FishingState)->bounce_speed + TASK(FishingState)->bounce_accel;
    total                             = TASK(FishingState)->bounce.unk_3C + step;
    TASK(FishingState)->bounce_speed  = step;
    TASK(FishingState)->bounce.unk_3C = total;
    if (total > 0 && TASK(FishingState)->bounce_accel == 0) {
        if (TASK(FishingState)->saved_index == 0) {
            TASK(FishingState)->bounce.unk_3C = 0;
        } else {
            TASK(FishingState)->bounce_speed = 0x40000;
            TASK(FishingState)->bounce_accel = -0x8000;
            slot                             = Actor_FindFreeSpawned() & BYTE_MASK;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xA;
            }
        }
    } else {
        if (TASK(FishingState)->bounce.unk_3C < 0 && TASK(FishingState)->bounce_accel != 0) {
            TASK(FishingState)->bounce_accel = 0;
            TASK(FishingState)->saved_index  = 0;
        } else {
            if (TASK(FishingState)->bounce.unk_3C > 0) {
                TASK(FishingState)->saved_index = 1;
            } else {
                TASK(FishingState)->saved_index = 0;
            }
        }
    }
    TASK(FishingState)->unk_5C = 0;
    if (TASK(FishingState)->bounce.half.key > 0) {
        TASK(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        TASK(FishingState)->tint_5D = 0;
    } else {
        TASK(FishingState)->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }
    TASK(FishingState)->tint_5E = TASK(FishingState)->tint_5D;
    TASK(FishingState)->tint_5F = TASK(FishingState)->tint_5D;
    cursor                      = TASK(FishingState)->cursor_10;
    if (cursor > 0) {
        Script_Request(2);
    } else if (cursor < 0) {
        Script_Request(0);
    } else {
        Script_Request(3);
    }
    Script_AnimStepLoop();
    TASK(FishingState)->counter_48 = 2;
    func_801E084C();
}
