#include "area030_04.h"

/* Clamps the work record's height to the retail range, then either
 * settles the record on arrival (clears motion and advances the state) or steps
 * its Y coordinate toward the target and updates X/Z from the current motion. */
/* func_801D23F4 */
MATCH void Fishing_LureFly(void) {
    s32           row;
    s32           target_y;
    s32           step;
    s32           current_y;
    s32           height;
    FishingState* work_d;
    FishingState* work_b;
    FishingState* work_e;
    FishingState* work_a;
    FishingState* work_c;

    height = SELF(FishingState)->cursor_10;
    if (height >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetCoordY.fixed = FISHING_CAMERA_Y_MAX;
    } else if (height < FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetCoordY.fixed = FISHING_CAMERA_Y_MIN;
    } else {
        g_AreaScrollTargetCoordY.fixed = height;
    }
    work_a    = SELF(FishingState);
    current_y = work_a->y_38.pos_y;
    target_y  = work_a->cursor_10;
    if (current_y == target_y) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        work_b                    = SELF(FishingState);
        work_b->timer             = 0;
        work_c                    = SELF(FishingState);
        FIELD(s32, work_b, 0x3Cu) = 0;
        work_b->bounce_speed      = 0;
        work_b->bounce_accel      = 0;
        work_c->step_index        = 0;
        if (g_AreaCameraMoving == 0) {
            work_c                = SELF(FishingState);
            g_AreaCameraSpeed     = 0;
            work_c->cursor_10     = 0;
            work_c->handler_index = (work_c->handler_index + 1);
        }
        Script_Select(4U);
    } else {
        row = work_a->cue_index * 8;
        if (current_y == (target_y + *(s32*)((u8*)&g_FishingLureFlyCueSteps + row))) {
            work_a->bounce_accel = *(s32*)((u8*)&D_801E1D5C + row);
        }
        work_d               = SELF(FishingState);
        step                 = work_d->bounce_speed + work_d->bounce_accel;
        work_d->bounce_speed = step;
        if (((work_d->cursor_10 + g_FishingLureFlyCueSteps[work_d->cue_index].height_offset) < work_d->y_38.pos_y) && (step < 0)) {
            work_d->bounce_speed = 0;
            work_d->bounce_accel = 0;
        }
        work_e                = SELF(FishingState);
        work_e->motion.unk_34 = (work_e->motion.unk_34 + work_e->pos_x);
        work_e->y_38.pos_y    = (work_e->y_38.pos_y - 0x4000);
        work_e->bounce.unk_3C = (work_e->bounce.unk_3C + work_e->bounce_speed);
        if (work_e->y_38.pos_y == TO_COORD(60)) {
            g_AreaCameraSpeed = 0x40;
        }
        Script_AnimStepLoop();
    }
    Area_AddGridActor();
}
