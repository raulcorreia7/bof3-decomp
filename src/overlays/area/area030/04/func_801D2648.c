#include "area030_04.h"

/* Advances the work record's motion and bounce timers and selects the walk animation direction. */
MATCH void func_801D2648(void) {
    s32 total;
    s32 step;
    s32 cursor;
    s16 slot;

    if (FISHING_STATE->step_index_0A != 0) {
        FISHING_STATE->step_index_0A -= 1;
        if (FISHING_STATE->step_index_0A == 0 && (s8)D_801E3210->unk_0F < FISHING_STATE->counter_07) {
            FISHING_STATE->step_index_0A = D_801E3210->unk_10;
            FISHING_STATE->counter_07 -= 1;
        }
    }
    FISHING_STATE->motion_34.unk_34 += FISHING_STATE->pos_x_0C;
    FISHING_STATE->y_38.pos_y += FISHING_STATE->cursor_10;
    step                            = FISHING_STATE->step_14 + FISHING_STATE->step_limit_20;
    total                           = FISHING_STATE->bounce_3C.unk_3C + step;
    FISHING_STATE->step_14          = step;
    FISHING_STATE->bounce_3C.unk_3C = total;
    if (total > 0 && FISHING_STATE->step_limit_20 == 0) {
        if (FISHING_STATE->saved_index_0B == 0) {
            FISHING_STATE->bounce_3C.unk_3C = 0;
        } else {
            FISHING_STATE->step_14       = 0x40000;
            FISHING_STATE->step_limit_20 = -0x8000;
            slot                         = Actor_FindFreeSlot() & 0xFF;
            if (slot != GAME_NONE) {
                g_ActorSlots[slot].header.flags = 1;
                g_ActorSlots[slot].type         = 0xA;
            }
        }
    } else {
        if (FISHING_STATE->bounce_3C.unk_3C < 0 && FISHING_STATE->step_limit_20 != 0) {
            FISHING_STATE->step_limit_20  = 0;
            FISHING_STATE->saved_index_0B = 0;
        } else {
            if (FISHING_STATE->bounce_3C.unk_3C > 0) {
                FISHING_STATE->saved_index_0B = 1;
            } else {
                FISHING_STATE->saved_index_0B = 0;
            }
        }
    }
    FISHING_STATE->unk_5C = 0;
    if (FISHING_STATE->bounce_3C.half.key_3E > 0) {
        FISHING_STATE->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        FISHING_STATE->tint_5D = 0;
    } else {
        FISHING_STATE->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }
    FISHING_STATE->tint_5E = FISHING_STATE->tint_5D;
    FISHING_STATE->tint_5F = FISHING_STATE->tint_5D;
    cursor                 = FISHING_STATE->cursor_10;
    if (cursor > 0) {
        Actor_RequestScript(2);
    } else if (cursor < 0) {
        Actor_RequestScript(0);
    } else {
        Actor_RequestScript(3);
    }
    func_8014D978();
    FISHING_STATE->counter_48 = 2;
    func_801E084C();
}
