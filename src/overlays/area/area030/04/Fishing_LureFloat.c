#include "area030_04.h"

/* Advances the work record's motion and bounce timers and selects the walk animation direction. */
/* func_801D2648 */
MATCH void Fishing_LureFloat(void) {
    s32 total;
    s32 step;
    s32 cursor;
    s16 slot;

    if (FISHING_STATE->step_index != 0) {
        FISHING_STATE->step_index -= 1;
        if (FISHING_STATE->step_index == 0 && (s8)g_FishingLureRow->unk_0F < FISHING_STATE->counter_07) {
            FISHING_STATE->step_index = g_FishingLureRow->unk_10;
            FISHING_STATE->counter_07 -= 1;
        }
    }
    FISHING_STATE->motion.unk_34 += FISHING_STATE->pos_x;
    FISHING_STATE->y_38.pos_y += FISHING_STATE->cursor_10;
    step                         = FISHING_STATE->step_14 + FISHING_STATE->step_limit;
    total                        = FISHING_STATE->bounce.unk_3C + step;
    FISHING_STATE->step_14       = step;
    FISHING_STATE->bounce.unk_3C = total;
    if (total > 0 && FISHING_STATE->step_limit == 0) {
        if (FISHING_STATE->saved_index == 0) {
            FISHING_STATE->bounce.unk_3C = 0;
        } else {
            FISHING_STATE->step_14    = 0x40000;
            FISHING_STATE->step_limit = -0x8000;
            slot                      = Actor_FindFreeSpawned() & BYTE_MASK;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xA;
            }
        }
    } else {
        if (FISHING_STATE->bounce.unk_3C < 0 && FISHING_STATE->step_limit != 0) {
            FISHING_STATE->step_limit  = 0;
            FISHING_STATE->saved_index = 0;
        } else {
            if (FISHING_STATE->bounce.unk_3C > 0) {
                FISHING_STATE->saved_index = 1;
            } else {
                FISHING_STATE->saved_index = 0;
            }
        }
    }
    FISHING_STATE->unk_5C = 0;
    if (FISHING_STATE->bounce.half.key > 0) {
        FISHING_STATE->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        FISHING_STATE->tint_5D = 0;
    } else {
        FISHING_STATE->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }
    FISHING_STATE->tint_5E = FISHING_STATE->tint_5D;
    FISHING_STATE->tint_5F = FISHING_STATE->tint_5D;
    cursor                 = FISHING_STATE->cursor_10;
    if (cursor > 0) {
        Script_Request(2);
    } else if (cursor < 0) {
        Script_Request(0);
    } else {
        Script_Request(3);
    }
    Script_AnimStepLoop();
    FISHING_STATE->counter_48 = 2;
    func_801E084C();
}
