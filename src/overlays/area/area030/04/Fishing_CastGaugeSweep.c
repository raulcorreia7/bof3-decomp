#include "area030_04.h"

/* Advances the active AREA030 panel animation (the 0xC scroll
 * position, the 0x10 spring) according to the panel mode, then draws the
 * panel window and the bar whose length follows the scroll position; mode 3
 * also seeds the next panel's position. */
/* func_801D1CF0 */
MATCH void Fishing_CastGaugeSweep(void) {
    FishingState* work;
    FishingState* fresh;
    FishingState* back;
    s32           speed;

    work  = SELF(FishingState);
    speed = work->step_delta;
    if (speed != 0) {
        switch (g_FishingRodRow->cast_sweep_direction) {
            case 0:
                work->pos_x = work->pos_x + speed;
                if ((s32)work->step_delta > 0 && work->pos_x >= 0xFF) {
                    work->pos_x      = 0xFF;
                    work->step_delta = -work->step_delta;
                } else {
                    back = SELF(FishingState);
                    if ((s32)back->step_delta < 0 && back->pos_x <= 0) {
                        back->pos_x      = 0;
                        back->step_delta = -back->step_delta;
                    }
                }
                break;
            case 1:
                if (work->pos_x == GAME_NONE) {
                    work->pos_x = 0;
                } else {
                    work->pos_x = work->pos_x + speed;
                    if (work->pos_x >= 0x100) {
                        work->pos_x = 0xFF;
                    }
                }
                break;
            case 2:
                if (work->cursor_10 < 0) {
                    work->cursor_10 = work->cursor_10 + speed;
                    if (work->cursor_10 >= 0) {
                        work->cursor_10 = -1;
                    }
                } else {
                    work->cursor_10 = work->cursor_10 + speed;
                }
                fresh        = SELF(FishingState);
                fresh->pos_x = fresh->pos_x + fresh->cursor_10;
                if (fresh->cursor_10 > 0) {
                    if (fresh->pos_x >= 0xFF) {
                        fresh->pos_x     = 0xFF;
                        fresh->cursor_10 = -fresh->cursor_10;
                    }
                } else if (fresh->pos_x <= 0) {
                    fresh->pos_x     = 0;
                    fresh->cursor_10 = 0;
                }
                break;
        }
    }
    Fishing_SetDrawMode(0, 2);
    Fishing_DrawSprite(16, 2, 135, 180);
    Fishing_DrawGaugeFill(136, 203, ((SELF(FishingState)->pos_x * 96) / 255), 2);
    if (D_80145E92[0] == 3) {
        SELF(FishingState)->origin_x = 0xB8;
        SELF(FishingState)->origin_y = 0xD1;
        SELF(FishingState)->handler_index += 1;
    }
}
