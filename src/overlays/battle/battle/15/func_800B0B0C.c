#include "battle_15.h"

/* Draws the three choice boxes 48 apart; bit 7 of the selection fixes one, else the hand marks it. */
MATCH void func_800B0B0C(s16 base_x, s16 base_y) {
    u8 slot;
    u8 selection;

    slot = 0;
    do {
        UI_WindowDraw(base_x + slot * 0x30, base_y, 45, 20, 0, g_WindowStyle);
        selection = g_Battle.selection;
        if (selection & 0x80) {
            if (slot == (selection & 0x7F)) {
                UI_TextDraw(base_x + 4 + slot * 0x30, base_y + 3, 0, MENU_LABEL_LENGTH, (u8*)&D_800B6D30[slot * 3]);
                func_801AF390(base_x + slot * 0x30, base_y, (u8*)D_800B6D28, 1);
            } else {
                UI_TextDraw(base_x + 4 + slot * 0x30, base_y + 3, UI_TEXT_DIM, MENU_LABEL_LENGTH, (u8*)&D_800B6D30[slot * 3]);
                func_801AF390(base_x + slot * 0x30, base_y, (u8*)D_800B6D20, 1);
            }
        } else {
            UI_TextDraw(base_x + 4 + slot * 0x30, base_y + 3, 0, MENU_LABEL_LENGTH, (u8*)&D_800B6D30[slot * 3]);
            func_801AF390(base_x + slot * 0x30, base_y, (u8*)D_800B6D20, 1);
        }
        slot++;
    } while (slot < 3);

    selection = g_Battle.selection;
    if (!(selection & 0x80)) {
        UI_CursorDraw(base_x + (selection & 0x7F) * 0x30, base_y + 4, 0);
    }
}
