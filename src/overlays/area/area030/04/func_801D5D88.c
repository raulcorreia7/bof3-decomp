#include "area030_04.h"

/* Advances the area-030 scrolling banner: steps the 3-byte frame table, bounces the strip between its ends,
 * and draws the three letter rows plus the page counter. */
MATCH void func_801D5D88(void) {
    s32           offset;
    s32           scroll;
    s32           previous;
    FishingState* work;

    u8 mode;

    mode = SELF(FishingState)->timer;
    if (mode == 0) {
        offset = SELF(FishingState)->step_index * 3;
        if (D_801E2008[offset] == GAME_NONE) {
            SELF(FishingState)->step_index = D_801E2009[offset];
            SELF(FishingState)->pos_x      = 0;
            SELF(FishingState)->step_delta = 4;
            SELF(FishingState)->cue_index  = 0;
        }
        Script_Select(D_801E2008[SELF(FishingState)->step_index * 3]);
        SELF(FishingState)->timer = D_801E2009[SELF(FishingState)->step_index * 3];
        SELF(FishingState)->step_index += 1;
    } else {
        SELF(FishingState)->timer = mode - 1;
        Script_AnimStepLoop();
    }
    Area_AddActor();
    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(21, 1, 50, 122);
    Fishing_DrawSprite(22, 1, 188, 122);
    Fishing_DrawSprite(16, 1, 54, 128);
    work     = SELF(FishingState);
    previous = work->step_index - 1;
    mode     = D_801E200A[previous * 3];
    if (mode == 0) {
        scroll      = work->pos_x + work->step_delta;
        work->pos_x = scroll;
        if ((s32)work->step_delta > 0) {
            if (scroll >= 97) {
                work->pos_x      = 0x60;
                work->step_delta = -work->step_delta;
            }
        } else if (scroll < 0) {
            work->pos_x      = 0;
            work->step_delta = -work->step_delta;
        }
    } else if (mode == 0x1 && !(g_FrameCount & 1)) {
        work->cue_index = work->cue_index + 1;
    }
    Fishing_DrawGaugeFill(57, 151, SELF(FishingState)->pos_x, 1);
    TEXT_Format(g_UiTextFormatBuffer, D_801D0C04, SELF(FishingState)->cue_index);
    UI_TextDrawAscii(172, 148, 0, g_UiTextFormatBuffer);
    Area_AddActor();
}
