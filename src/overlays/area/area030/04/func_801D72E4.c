#include "area030_04.h"

/* Draws the area-030 party bars: the actor's own bar row, the
 * member bars and the name text. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D72E4(s16 panel_x, s16 panel_y) {
    u16 value;
    u16 health;
    u8  bar_index;
    u8  bar_count;
    u8  bar_slot;
    s16 row_y;
    s32 offset;
    s32 count;
    s32 scroll_pos;
    s32 member;
    u8* text;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    UI_WindowDraw(panel_x & HALF_MASK, panel_y & HALF_MASK, 242, 159, UI_WINDOW_OPEN_ALL, (s32)g_WindowStyle);
    if (TASK(FishingState)->counter_08 != 0) {
        if (TASK(FishingState)->timer == 0) {
            health = TASK(FishingState)->bounce.half.unk_3C;
            if (TASK(FishingState)->bounce.half.key != health) {
                TASK(FishingState)->bounce_accel    = (s32)(health * 9);
                TASK(FishingState)->bounce.half.key = (s16)TASK(FishingState)->bounce.half.unk_3C;
            }
            if ((s8)TASK(FishingState)->counter_08 > 0) {
                if (--TASK(FishingState)->bounce_speed < 0) {
                    TASK(FishingState)->bounce_speed = 0x35;
                }
            }
            TASK(FishingState)->timer      = (u8)(TASK(FishingState)->timer + 1);
            TASK(FishingState)->step_index = (u8)(TASK(FishingState)->step_index + 1);
        }
        if (TASK(FishingState)->step_index == 0) {
            scroll_pos = TASK(FishingState)->bounce_speed;
            if (scroll_pos == TASK(FishingState)->bounce_accel) {
                TASK(FishingState)->timer            = 0U;
                TASK(FishingState)->counter_08       = 0U;
                member                               = Actor_FindFreeSpawned() & BYTE_MASK;
                g_SpawnedActors[member].header.flags = 1;
                g_SpawnedActors[member].type         = 0x1A;
                g_SpawnedActors[member].header.mode  = 0x10;
                g_SpawnedActors[member].header.step  = (u8)TASK(FishingState)->bounce.half.key;
            } else {
                if ((s8)TASK(FishingState)->counter_08 > 0) {
                    TASK(FishingState)->bounce_speed = scroll_pos - 1;
                    if (TASK(FishingState)->bounce_speed < 0) {
                        TASK(FishingState)->bounce_speed = 0x35;
                    }
                }
                TASK(FishingState)->step_index = (u8)(TASK(FishingState)->step_index + 1);
            }
        } else {
            TASK(FishingState)->step_index = (u8)(TASK(FishingState)->step_index + 1);
            if (TASK(FishingState)->step_index == 4) {
                TASK(FishingState)->step_index = 0U;
                if ((s8)TASK(FishingState)->counter_08 < 0) {
                    if (++TASK(FishingState)->bounce_speed >= 0x36) {
                        TASK(FishingState)->bounce_speed = 0;
                    }
                }
            }
        }
    }
    bar_slot = (u8)TASK(FishingState)->step_index;
    row_y    = panel_y + 25;
    if (bar_slot != 0) {
        if (TASK(FishingState)->counter_08 == 1) {
            offset = bar_slot * 3 + 12;
            row_y  = panel_y + offset;
        } else {
            offset = bar_slot * 3 - 25;
            row_y  = panel_y - offset;
        }
        bar_count = 10;
    } else {
        bar_count = 9;
    }
    bar_index = (u8)TASK(FishingState)->bounce_speed;
    count     = 0;
    if (bar_count != 0) {
        do {
            value = D_801E2120[bar_index & BYTE_MASK];
            if (value != 0xFFFF) {
                UI_TextDraw(panel_x + 6, row_y + count * 13, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, value));
            }
            bar_index += 1;
            if ((u32)(bar_index & BYTE_MASK) >= 0x36U) {
                bar_index = 0;
            }
            count += 1;
        } while (count < bar_count);
    }
    UI_WindowDraw(panel_x & HALF_MASK, (panel_y + 6) & HALF_MASK, 242, 14, 0, CHARACTER_BLOCK->window_style);
    UI_WindowDraw(panel_x & HALF_MASK, (panel_y + 148) & HALF_MASK, 242, 11, UI_WINDOW_OPEN_BOTTOM_LEFT | UI_WINDOW_OPEN_BOTTOM_RIGHT, CHARACTER_BLOCK->window_style);
    UI_TextDraw((s16)(panel_x + 61), (s16)(panel_y + 6), 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801E2114[TASK(FishingState)->bounce.half.unk_3C]));
    func_801D7784(panel_x, panel_y);
    text = (u8*)g_UiTextFormatBuffer;
    TEXT_Format(text, D_801D0C08, TASK(FishingState)->bounce.half.unk_3C + 1);
    UI_TextDrawGlyphString((s16)(panel_x + 202), (s16)(panel_y + 146), 0U, text);
}
#else
INCLUDE_ASM(func_801D72E4);
#endif
