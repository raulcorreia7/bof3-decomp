#include "area030_04.h"

/* Draws the area-030 HUD cell grid: steps the page timer, draws each of the 32 cells with its selected color,
 * and advances the page row when the timer expires. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D6684(void) {
    s32*  word_ptr;
    s32   kind;
    s32   x;
    s32   y;
    s32   color;
    s32   page;
    s32   x_fixed;
    s32   col;
    s32   y_sel;
    s32   row;
    s32   y_other;
    u8*   cell_ptr;
    u8*   cell_table;
    u8    cell;
    u8    timer;
    void* spad5;
    void* spad6;
    void* spad1;
    void* spad0;
    void* spad2;
    void* spad3;
    void* spad4;

    spad0 = g_Task;
    if (FIELD(u8, spad0, 0xAu) != 0) {
        func_801D2034(0xD4, 0x8A, 0U, (FIELD(u8, spad0, 0xBu) + 1) & BYTE_MASK);
        page = g_Task->timer / 12;
    } else {
        FIELD(u8, spad0, 0x9u) = (u8)(FIELD(u8, spad0, 0x9u) + 1);
        spad5                  = g_Task;
        page                   = FIELD(u8, spad5, 0x9u) / 12;
        if (*((FIELD(u8, spad5, 0xBu) * 8) + &D_801E2050 + (page & BYTE_MASK)) == GAME_NONE) {
            FIELD(u8, spad5, 0xAu) = 0x32U;
        }
    }
    row = 0;
    if ((g_Task->unk_0A == 0) && (*((g_Task->param.unk_0B * 8) + &D_801E2050 + (page & BYTE_MASK)) == 1) &&
        ((u32)((g_Task->timer % 12) & BYTE_MASK) < 0xAU)) {
        Actor_StepAnimLoop();
    }
    word_ptr   = &D_801E2070;
    word_ptr   = &D_801E2070;
    y_sel      = TO_COORD(158);
    y_other    = TO_COORD(155);
    cell_table = &D_801E2050;
    cell_table = &D_801E2050;
    do {
        col      = 0;
        x_fixed  = TO_COORD(132);
        cell_ptr = cell_table;
    loop_11:
        cell = *cell_ptr;
        kind = cell & BYTE_MASK;
        if (kind != GAME_NONE) {
            spad1 = g_Task;
            if (row == FIELD(u8, spad1, 0xBu)) {
                if ((u32)((FIELD(u8, spad1, 0x9u) % 12) & BYTE_MASK) < 0xAU) {
                    x = x_fixed >> 0x10;
                    if (col == (page & BYTE_MASK)) {
                        UI_DrawText((s16)x, (s16)(y_other >> 0x10), kind, 1U, ((kind * 2) + &D_801E2070));
                    } else {
                        goto block_17; /* shared cell/row draw join */
                    }
                } else {
                    x = x_fixed >> 0x10;
                block_17:
                    y     = y_sel >> 0x10;
                    color = (*cell_ptr * 3) & BYTE_MASK;
                    goto block_19; /* shared cell/row draw join */
                }
            } else {
                x     = x_fixed >> 0x10;
                y     = y_sel >> 0x10;
                color = (7 - cell) & BYTE_MASK;
            block_19:
                UI_DrawTextString((s16)x, (s16)y, color, 1, (u32)((kind * 2) + &D_801E2070));
            }
            x_fixed += TO_COORD(12);
            col += 1;
            cell_ptr += 1;
            if (col >= 8) {
            } else {
                goto loop_11; /* shared cell/row draw join */
            }
        }
        y_sel += TO_COORD(13);
        y_other += TO_COORD(13);
        row += 1;
        cell_table += 8;
    } while (row < 4);
    Area_AddActor();
    spad2 = g_Task;
    timer = FIELD(u8, spad2, 0xAu);
    if (timer != 0) {
        FIELD(u8, spad2, 0xAu) = (u8)(timer - 1);
        spad3                  = g_Task;
        if (FIELD(u8, spad3, 0xAu) == 0) {
            FIELD(u8, spad3, 0x9u) = 0U;
            spad6                  = g_Task;
            FIELD(u8, spad6, 0xBu) = (u8)(FIELD(u8, spad6, 0xBu) + 1);
            spad4                  = g_Task;
            if (FIELD(u8, spad4, 0xBu) >= 4U) {
                FIELD(u8, spad4, 0xBu) = 0U;
            }
        }
    }
}
#else
INCLUDE_ASM(func_801D6684);
#endif
