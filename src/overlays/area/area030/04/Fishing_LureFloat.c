#include "area030_04.h"

/* Advances the work record's motion and bounce timers and selects the walk animation direction. */
/* func_801D2648 */
MATCH void Fishing_LureFloat(void) {
    s32 total;
    s32 step;
    s32 cursor;
    s16 slot;

    if (SELF(FishingState)->step_index != 0) {
        SELF(FishingState)->step_index -= 1;
        if (SELF(FishingState)->step_index == 0 && (s8)g_FishingLureRow->unk_0F < SELF(FishingState)->counter_07) {
            SELF(FishingState)->step_index = g_FishingLureRow->unk_10;
            SELF(FishingState)->counter_07 -= 1;
        }
    }
    SELF(FishingState)->motion.unk_34 += SELF(FishingState)->pos_x;
    SELF(FishingState)->y_38.pos_y += SELF(FishingState)->cursor_10;
    step                              = SELF(FishingState)->bounce_speed + SELF(FishingState)->bounce_accel;
    total                             = SELF(FishingState)->bounce.unk_3C + step;
    SELF(FishingState)->bounce_speed  = step;
    SELF(FishingState)->bounce.unk_3C = total;
    if (total > 0 && SELF(FishingState)->bounce_accel == 0) {
        if (SELF(FishingState)->saved_index == 0) {
            SELF(FishingState)->bounce.unk_3C = 0;
        } else {
            SELF(FishingState)->bounce_speed = 0x40000;
            SELF(FishingState)->bounce_accel = -0x8000;
            slot                             = Actor_FindFreeSpawned() & BYTE_MASK;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xA;
            }
        }
    } else {
        if (SELF(FishingState)->bounce.unk_3C < 0 && SELF(FishingState)->bounce_accel != 0) {
            SELF(FishingState)->bounce_accel = 0;
            SELF(FishingState)->saved_index  = 0;
        } else {
            if (SELF(FishingState)->bounce.unk_3C > 0) {
                SELF(FishingState)->saved_index = 1;
            } else {
                SELF(FishingState)->saved_index = 0;
            }
        }
    }
    SELF(FishingState)->unk_5C = 0;
    if (SELF(FishingState)->bounce.half.key > 0) {
        SELF(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(FishingState)->tint_5D = 0;
    } else {
        SELF(FishingState)->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }
    SELF(FishingState)->tint_5E = SELF(FishingState)->tint_5D;
    SELF(FishingState)->tint_5F = SELF(FishingState)->tint_5D;
    cursor                      = SELF(FishingState)->cursor_10;
    if (cursor > 0) {
        Script_Request(2);
    } else if (cursor < 0) {
        Script_Request(0);
    } else {
        Script_Request(3);
    }
    Script_AnimStepLoop();
    SELF(FishingState)->counter_48 = 2;
    func_801E084C();
}
