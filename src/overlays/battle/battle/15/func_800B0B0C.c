#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800B0B0C(s16 base_x, s16 base_y) {
    volatile u16 y_value;
    s16          cursor_y;
    u8           slot;
    u8           selection_byte;
    u8           active_slot;
    const u8*    palette;
    s32          slot_offset;
    s32          slot_times_3;

    y_value  = base_y;
    cursor_y = base_y + 3;
    slot     = 0u;
    do {
        slot_offset  = (s32)slot * 0x30;
        slot_times_3 = (s32)slot * 3;

        UI_WindowDraw((u16)(base_x + slot_offset), y_value, 45u, 20u, 0u, (s32)g_WindowStyle);

        selection_byte = g_Battle.selection;
        if (selection_byte & 0x80u) {
            active_slot = selection_byte & 0x7Fu;
            if (slot == active_slot) {
                UI_TextDraw((s16)(base_x + slot_offset + 4), cursor_y, 0u, MENU_LABEL_LENGTH, &D_800B6D30[slot_times_3]);
                palette = D_800B6D28;
            } else {
                UI_TextDraw((s16)(base_x + slot_offset + 4), cursor_y, UI_TEXT_DIM, MENU_LABEL_LENGTH, &D_800B6D30[slot_times_3]);
                palette = D_800B6D20;
            }
        } else {
            UI_TextDraw((s16)(base_x + slot_offset + 4), cursor_y, 0u, MENU_LABEL_LENGTH, &D_800B6D30[slot_times_3]);
            palette = D_800B6D20;
        }
        func_801AF390((s16)(base_x + slot_offset), (s16)base_y, palette, 1);

        slot += 1u;
    } while (BATTLER_IS_PLAYER(slot));

    selection_byte = g_Battle.selection;

    if (!(selection_byte & 0x80u)) {
        active_slot = selection_byte & 0x7Fu;
        UI_CursorDraw((u16)(base_x + (s32)active_slot * 0x30), (u16)(y_value + 4u), 0);
    }
}
#else
INCLUDE_ASM(func_800B0B0C);
#endif
