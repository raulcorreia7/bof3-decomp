#include "area030_04.h"

/* Draws the area-030 HUD cell grid: steps the page timer, draws each of the 32 cells with its selected color,
 * and advances the page row when the timer expires. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D6684(void) {
    u8(*cells)[8];
    u8* cell_ptr;
    u8(*glyphs)[2];
    s32 row;
    s32 col;
    s32 x;
    s32 y;
    s32 y_page;
    u8  page;
    u8  cell;

    if (SELF(FishingState)->step_index != 0) {
        func_801D2034(0xD4, 0x8A, 0, (u8)(SELF(FishingState)->saved_index + 1));
        page = SELF(FishingState)->timer / 12;
    } else {
        SELF(FishingState)->timer++;
        page = SELF(FishingState)->timer / 12;
        if (D_801E2050[SELF(FishingState)->saved_index][page] == 0xFF) {
            SELF(FishingState)->step_index = 50;
        }
    }
    row = 0;
    if (SELF(FishingState)->step_index == 0 && D_801E2050[SELF(FishingState)->saved_index][page] == 1 && (u8)(SELF(FishingState)->timer % 12) < 10) {
        Script_AnimStepLoop();
    }
    glyphs = D_801E2070;
    y      = TO_COORD(158);
    y_page = TO_COORD(155);
    cells  = D_801E2050;
    do {
        col      = 0;
        x        = TO_COORD(132);
        cell_ptr = *cells;
    next_cell:
        cell = *cell_ptr;
        if (cell != 0xFF) {
            if (row == SELF(FishingState)->saved_index) {
                if ((u8)(SELF(FishingState)->timer % 12) < 10 && col == page) {
                    UI_TextDraw(x >> 16, y_page >> 16, cell, 1, glyphs[cell]);
                } else {
                    UI_TextDrawString(x >> 16, y >> 16, (u8)(*cell_ptr * 3), 1, glyphs[*cell_ptr]);
                }
            } else {
                UI_TextDrawString(x >> 16, y >> 16, (u8)(7 - cell), 1, glyphs[cell]);
            }
            x += TO_COORD(12);
            col++;
            cell_ptr++;
            if (col < 8) {
                goto next_cell;
            }
        }
        y += TO_COORD(13);
        y_page += TO_COORD(13);
        row++;
        cells++;
    } while (row < 4);
    Area_AddActor();
    if (SELF(FishingState)->step_index != 0) {
        SELF(FishingState)->step_index--;
        if (SELF(FishingState)->step_index == 0) {
            SELF(FishingState)->timer = 0;
            SELF(FishingState)->saved_index++;
            if (SELF(FishingState)->saved_index >= 4) {
                SELF(FishingState)->saved_index = 0;
            }
        }
    }
}
#else
INCLUDE_ASM(func_801D6684);
#endif
