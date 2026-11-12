#include "area030_04.h"

/* Advances the area-030 scrolling banner: steps the 3-byte frame table, bounces the strip between its ends,
 * and draws the three letter rows plus the page counter. */
MATCH void func_801D5D88(void) {
    s32           offset;
    s32           scroll;
    s32           previous;
    FishingState* work;

    u8 mode;

    mode = FISHING_STATE->step_timer_09;
    if (mode == 0) {
        offset = FISHING_STATE->step_index_0A * 3;
        if (D_801E2008[offset] == GAME_NONE) {
            FISHING_STATE->step_index_0A = D_801E2009[offset];
            FISHING_STATE->pos_x_0C      = 0;
            FISHING_STATE->step_delta_18 = 4;
            FISHING_STATE->cue_index_06  = 0;
        }
        Actor_SelectScript(D_801E2008[FISHING_STATE->step_index_0A * 3]);
        FISHING_STATE->step_timer_09 = D_801E2009[FISHING_STATE->step_index_0A * 3];
        FISHING_STATE->step_index_0A += 1;
    } else {
        FISHING_STATE->step_timer_09 = mode - 1;
        Actor_StepAnimLoop();
    }
    Area_AddActor();
    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(21, 1, 50, 122);
    Fishing_DrawSprite(22, 1, 188, 122);
    Fishing_DrawSprite(16, 1, 54, 128);
    work     = FISHING_STATE;
    previous = work->step_index_0A - 1;
    mode     = D_801E200A[previous * 3];
    if (mode == 0) {
        scroll         = work->pos_x_0C + work->step_delta_18;
        work->pos_x_0C = scroll;
        if ((s32)work->step_delta_18 > 0) {
            if (scroll >= 97) {
                work->pos_x_0C      = 0x60;
                work->step_delta_18 = -work->step_delta_18;
            }
        } else if (scroll < 0) {
            work->pos_x_0C      = 0;
            work->step_delta_18 = -work->step_delta_18;
        }
    } else if (mode == 0x1 && !(g_FrameCount & 1)) {
        work->cue_index_06 = work->cue_index_06 + 1;
    }
    Fishing_DrawGaugeFill(57, 151, FISHING_STATE->pos_x_0C, 1);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, FISHING_STATE->cue_index_06);
    UI_DrawAsciiString(172, 148, 0, g_UiFormatBuffer);
    Area_AddActor();
}
