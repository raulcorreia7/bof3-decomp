#include "battle_15.h"

/* nonmatching: first difference +0x0004; retail keeps base_x in s5, the loop counter in s4 and y pre-shifted in s6, ours rotates the saved registers. */
#ifdef NON_MATCHING
NON_MATCHING void func_800B0B0C(s16 base_x, s16 base_y) {
    volatile u16 y_value;
    s16          cursor_y;
    u8           slot;
    u8           selection_byte;
    u8           active_slot;
    s32          palette_index;
    s32          slot_offset;
    s32          slot_times_3;
    y_value  = base_y;
    cursor_y = base_y + 3;

    slot = 0u;
    do {
        slot_offset  = (s32)slot * 0x30;
        slot_times_3 = (s32)slot * 3;

        UI_DrawWindow((s32)(u16)(base_x + slot_offset), (s32)y_value, 45u, 20u, 0u, (s32)g_WindowStyle);

        selection_byte = g_BattleRowCursor;

        if (selection_byte & 0x80u) {
            active_slot = selection_byte & 0x7Fu;
            if (slot == active_slot) {
                UI_DrawText((s16)(base_x + (slot_offset + 4)), cursor_y, 0u, 0x10u, (D_800B6D30 + slot_times_3));
                palette_index = (s32)D_800B6D28;
            } else {
                UI_DrawText((s16)(base_x + (slot_offset + 4)), cursor_y, 7u, 0x10u, (D_800B6D30 + slot_times_3));
                palette_index = (s32)D_800B6D20;
            }
        } else {
            UI_DrawText((s16)(base_x + (slot_offset + 4)), cursor_y, 0u, 0x10u, (D_800B6D30 + slot_times_3));
            palette_index = (s32)D_800B6D20;
        }
        UI_DrawSpriteRun((s16)(base_x + slot_offset), base_y, (void*)(palette_index), 1u);

        slot += 1u;
    } while (BATTLER_IS_PLAYER(slot));

    selection_byte = g_BattleRowCursor;

    if (!(selection_byte & 0x80u)) {
        active_slot = selection_byte & 0x7Fu;
        Menu_DrawCursorSprite((u16)(base_x + (s32)active_slot * 0x30), (u16)(y_value + 4u), 0);
    }
}
#else
INCLUDE_ASM(func_800B0B0C);
#endif
