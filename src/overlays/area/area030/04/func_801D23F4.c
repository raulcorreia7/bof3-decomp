#include "area030_04.h"

/* Clamps the work record's height to the retail range, then either
 * settles the record on arrival (clears motion and advances the state) or steps
 * its Y coordinate toward the target and updates X/Z from the current motion. */
MATCH void func_801D23F4(void) {
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
    if (height > 0x3BFFFF) {
        g_AreaScrollTargetY = 0x3C0000;
    } else if (height <= 0x14FFFF) {
        g_AreaScrollTargetY = 0x150000;
    } else {
        g_AreaScrollTargetY = (u32)height;
    }
    work_a    = (FishingState*)g_SpadWork;
    current_y = work_a->y_38.pos_y;
    target_y  = work_a->cursor_10;
    if (current_y == target_y) {
        SND_PlayCue(EMI_CUE_ID(2, 1));
        work_b                    = (FishingState*)g_SpadWork;
        work_b->step_timer_09     = 0;
        work_c                    = (FishingState*)g_SpadWork;
        FIELD(s32, work_b, 0x3Cu) = 0;
        work_b->step_14           = 0;
        work_b->step_limit_20     = 0;
        work_c->step_index_0A     = 0;
        if (g_AreaCameraMoving == 0) {
            work_c                   = (FishingState*)g_SpadWork;
            g_AreaCameraStep         = 0;
            work_c->cursor_10        = 0;
            work_c->handler_index_01 = (u8)(work_c->handler_index_01 + 1);
        }
        Actor_SelectScript(4U);
    } else {
        row = work_a->cue_index_06 * 8;
        if (current_y == (target_y + *(s32*)((u8*)&D_801E1D58 + row))) {
            work_a->step_limit_20 = (s32) * (s32*)((u8*)&D_801E1D5C + row);
        }
        work_d          = (FishingState*)g_SpadWork;
        step            = work_d->step_14 + work_d->step_limit_20;
        work_d->step_14 = step;
        if (((work_d->cursor_10 + D_801E1D58[work_d->cue_index_06].offset_00) < work_d->y_38.pos_y) &&
            (step < 0)) {
            work_d->step_14       = 0;
            work_d->step_limit_20 = 0;
        }
        work_e                   = (FishingState*)g_SpadWork;
        work_e->motion_34.unk_34 = (s32)(work_e->motion_34.unk_34 + work_e->pos_x_0C);
        work_e->y_38.pos_y       = (s32)(work_e->y_38.pos_y - 0x4000);
        work_e->bounce_3C.unk_3C = (s32)(work_e->bounce_3C.unk_3C + work_e->step_14);
        if (work_e->y_38.pos_y == 0x3C0000) {
            g_AreaCameraStep = 0x40;
        }
        func_8014D978();
    }
    func_8014D290();
}
