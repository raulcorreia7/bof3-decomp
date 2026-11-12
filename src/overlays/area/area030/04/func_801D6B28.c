#include "area030_04.h"

/* Refreshes the AREA030 HUD panel state, clamps the two tracked x
 * positions into their visible ranges, then routes the two marker helpers. */
MATCH void func_801D6B28(s8 panel_kind) {
    s32 left_x;
    s32 right_x;

    Area_AddActor();
    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(21, 1, 50, 150);
    Fishing_DrawSprite(22, 1, 188, 150);
    Fishing_DrawSprite(17, 1, 54, 156);

    {
        FishingState* work;
        FishingState* shown;
        FishingState* pair;
        s32           value;

        work   = (FishingState*)g_Task;
        value  = work->pos_x_0C;
        left_x = (value < 57) ? 57 : ((value >= 122) ? 121 : value);

        shown          = (FishingState*)g_Task;
        work->pos_x_0C = left_x;

        value   = shown->cursor_10;
        right_x = (value < 65) ? 65 : ((value >= 149) ? 148 : value);

        pair             = (FishingState*)g_Task;
        shown->cursor_10 = right_x;

        if ((pair->cursor_10 < pair->pos_x_0C) || (pair->pos_x_0C + 0x20 < pair->cursor_10)) {
            Fishing_DrawReelCursor(pair->pos_x_0C, 0xB3, 0x20u, ((pair->cue_index_06 & 0x7u) << 1), 1u, 1);
        } else {
            Fishing_DrawReelCursor(pair->pos_x_0C, 0xB3, 0x20u, ((pair->cue_index_06 & 0x7u) << 1), 1u, 0);
        }
    }

    if ((panel_kind & BYTE_MASK) == 0) {
        Fishing_DrawFishArrow(*(s16*)(TASK_BYTES + 0x10u), 0xB3, 0, 1u);
    } else {
        Fishing_DrawFishArrow(*(s16*)(TASK_BYTES + 0x10u), 0xB3, 1, 1u);
    }
}
