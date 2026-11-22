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

    height = FISHING_STATE->cursor_10;
    if (height >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MAX;
    } else if (height < FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MIN;
    } else {
        g_AreaScrollTargetY = height;
    }
    work_a    = (FishingState*)g_Task;
    current_y = work_a->y_38.pos_y;
    target_y  = work_a->cursor_10;
    if (current_y == target_y) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        work_b                    = (FishingState*)g_Task;
        work_b->step_timer        = 0;
        work_c                    = (FishingState*)g_Task;
        FIELD(s32, work_b, 0x3Cu) = 0;
        work_b->step_14           = 0;
        work_b->step_limit        = 0;
        work_c->step_index        = 0;
        if (g_AreaCameraMoving == 0) {
            work_c                = (FishingState*)g_Task;
            g_AreaCameraStep      = 0;
            work_c->cursor_10     = 0;
            work_c->handler_index = (work_c->handler_index + 1);
        }
        Script_Select(4U);
    } else {
        row = work_a->cue_index * 8;
        if (current_y == (target_y + *(s32*)((u8*)&g_FishingLureFlyCueSteps + row))) {
            work_a->step_limit = *(s32*)((u8*)&D_801E1D5C + row);
        }
        work_d          = (FishingState*)g_Task;
        step            = work_d->step_14 + work_d->step_limit;
        work_d->step_14 = step;
        if (((work_d->cursor_10 + g_FishingLureFlyCueSteps[work_d->cue_index].height_offset) < work_d->y_38.pos_y) && (step < 0)) {
            work_d->step_14    = 0;
            work_d->step_limit = 0;
        }
        work_e                = (FishingState*)g_Task;
        work_e->motion.unk_34 = (work_e->motion.unk_34 + work_e->pos_x);
        work_e->y_38.pos_y    = (work_e->y_38.pos_y - 0x4000);
        work_e->bounce.unk_3C = (work_e->bounce.unk_3C + work_e->step_14);
        if (work_e->y_38.pos_y == TO_COORD(60)) {
            g_AreaCameraStep = 0x40;
        }
        Script_AnimStepLoop();
    }
    Area_AddGridActor();
}
