#include "area030_04.h"

/* Advances the active AREA030 panel animation (the 0xC scroll
 * position, the 0x10 spring) according to the panel mode, then draws the
 * panel window and the bar whose length follows the scroll position; mode 3
 * also seeds the next panel's position. */
MATCH void func_801D1CF0(void) {
    FishingState* work;
    FishingState* fresh;
    FishingState* back;
    s32           speed;

    work  = (FishingState*)SP_REF(u8*, 0x44u);
    speed = (s32)work->step_delta_18;
    if (speed != 0) {
        switch (D_801E320C->unk_01) {
            case 0:
                work->pos_x_0C = work->pos_x_0C + speed;
                if ((s32)work->step_delta_18 > 0 && work->pos_x_0C >= 0xFF) {
                    work->pos_x_0C      = 0xFF;
                    work->step_delta_18 = (u32) - (s32)work->step_delta_18;
                } else {
                    back = (FishingState*)SP_REF(u8*, 0x44u);
                    if ((s32)back->step_delta_18 < 0 && back->pos_x_0C <= 0) {
                        back->pos_x_0C      = 0;
                        back->step_delta_18 = (u32) - (s32)back->step_delta_18;
                    }
                }
                break;
            case 1:
                if (work->pos_x_0C == GAME_NONE) {
                    work->pos_x_0C = 0;
                } else {
                    work->pos_x_0C = work->pos_x_0C + speed;
                    if (work->pos_x_0C >= 0x100) {
                        work->pos_x_0C = 0xFF;
                    }
                }
                break;
            case 2:
                if ((s32)work->cursor_10 < 0) {
                    work->cursor_10 = work->cursor_10 + speed;
                    if (work->cursor_10 >= 0) {
                        work->cursor_10 = -1;
                    }
                } else {
                    work->cursor_10 = work->cursor_10 + speed;
                }
                fresh           = (FishingState*)SP_REF(u8*, 0x44u);
                fresh->pos_x_0C = fresh->pos_x_0C + fresh->cursor_10;
                if (fresh->cursor_10 > 0) {
                    if (fresh->pos_x_0C >= 0xFF) {
                        fresh->pos_x_0C  = 0xFF;
                        fresh->cursor_10 = -fresh->cursor_10;
                    }
                } else if (fresh->pos_x_0C <= 0) {
                    fresh->pos_x_0C  = 0;
                    fresh->cursor_10 = 0;
                }
                break;
        }
    }
    func_801E0C80(0, 2);
    func_801E0DCC(0x10, 2, 0x87, 0xB4);
    func_801D1B88(0x88, 0xCB, (s16)((FISHING_STATE->pos_x_0C * 0x60) / 255), 2);
    if (D_80145E92[0] == 3) {
        FISHING_STATE->origin_x_2E = 0xB8;
        FISHING_STATE->origin_y_30 = 0xD1;
        FISHING_STATE->handler_index_01 += 1;
    }
}
