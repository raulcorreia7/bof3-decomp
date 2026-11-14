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
    s16 bar_y;
    s16 bar_x;
    s32 count;
    s32 scroll_pos;
    s32 member;
    u8* text;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    UI_DrawWindow(panel_x & HALF_MASK, panel_y & HALF_MASK, 242, 159, 0xF0, (s32)g_WindowStyle);
    if (FISHING_STATE->counter_08 != 0) {
        if (FISHING_STATE->step_timer_09 == 0) {
            health = FISHING_STATE->bounce_3C.half.unk_3C;
            if (FISHING_STATE->bounce_3C.half.key_3E != health) {
                FISHING_STATE->step_limit_20         = (s32)(health * 9);
                FISHING_STATE->bounce_3C.half.key_3E = (s16)FISHING_STATE->bounce_3C.half.unk_3C;
            }
            if ((s8)FISHING_STATE->counter_08 > 0) {
                scroll_pos             = FISHING_STATE->step_14 - 1;
                FISHING_STATE->step_14 = scroll_pos;
                if (scroll_pos < 0) {
                    FISHING_STATE->step_14 = 0x35;
                }
            }
            FISHING_STATE->step_timer_09 = (u8)(FISHING_STATE->step_timer_09 + 1);
            FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
        }
        if (FISHING_STATE->step_index_0A == 0) {
            scroll_pos = FISHING_STATE->step_14;
            if (scroll_pos == FISHING_STATE->step_limit_20) {
                FISHING_STATE->step_timer_09                = 0U;
                FISHING_STATE->counter_08                   = 0U;
                member                                      = Actor_FindFreeSlot() & BYTE_MASK;
                g_SpawnedActors[member].header.flags        = 1;
                g_SpawnedActors[member].type                = 0x1A;
                g_SpawnedActors[member].header.mode         = 0x10;
                *(s16*)&g_SpawnedActors[member].header.step = (s16)FISHING_STATE->bounce_3C.half.key_3E;
            } else {
                scroll_pos = scroll_pos - 1;
                if ((s8)FISHING_STATE->counter_08 > 0) {
                    FISHING_STATE->step_14 = scroll_pos;
                    if (scroll_pos < 0) {
                        FISHING_STATE->step_14 = 0x35;
                    }
                }
                FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
            }
        } else {
            FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
            if (FISHING_STATE->step_index_0A == 4) {
                FISHING_STATE->step_index_0A = 0U;
                if ((s8)FISHING_STATE->counter_08 < 0) {
                    scroll_pos             = FISHING_STATE->step_14 + 1;
                    FISHING_STATE->step_14 = scroll_pos;
                    if (scroll_pos >= 0x36) {
                        FISHING_STATE->step_14 = 0;
                    }
                }
            }
        }
    }
    bar_slot = (u8)FISHING_STATE->step_index_0A;
    bar_y    = panel_y + 25;
    if (bar_slot != 0) {
        if (FISHING_STATE->counter_08 == 1) {
            bar_y = (s16)(panel_y + ((bar_slot * 3) + 12));
        } else {
            bar_y = (s16)(panel_y - ((bar_slot * 3) - 25));
        }
        bar_count = 10;
    } else {
        bar_count = 9;
    }
    bar_index = (u8)FISHING_STATE->step_14;
    count     = 0;
    if (bar_count != 0) {
        bar_x = (s16)(panel_x + 6);
        do {
            value = D_801E2120[bar_index & BYTE_MASK];
            if (value != 0xFFFF) {
                UI_DrawText(bar_x, bar_y, 0, 0xFFU, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, value));
            }
            bar_index += 1;
            if ((u32)(bar_index & BYTE_MASK) >= 0x36U) {
                bar_index = 0;
            }
            count += 1;
            bar_y += 13;
        } while (count < bar_count);
    }
    UI_DrawWindow(panel_x & HALF_MASK, (panel_y + 6) & HALF_MASK, 242, 14, 0, (s32)g_WindowStyle);
    UI_DrawWindow(panel_x & HALF_MASK, (panel_y + 148) & HALF_MASK, 242, 11, 0x30, (s32)g_WindowStyle);
    health = FISHING_STATE->bounce_3C.half.unk_3C;
    UI_DrawText((s16)(panel_x + 61), (s16)(panel_y + 6), 0, 0xFFU, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801E2114[health]));
    func_801D7784((u16)panel_x, (u16)panel_y);
    text = (u8*)g_UiFormatBuffer;
    TEXT_Format(text, D_801D0C08, health + 1);
    UI_DrawGlyphString((s16)(panel_x + 202), (s16)(panel_y + 146), 0U, text);
}
#else
INCLUDE_ASM(func_801D72E4);
#endif
