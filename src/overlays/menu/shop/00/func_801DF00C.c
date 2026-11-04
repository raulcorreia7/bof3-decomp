#include "shop_00.h"

/* nonmatching unmeasured: tried the candidate frames at 0x70 against the retail 0x50 - twelve locals stay live and s2
 * is saved. resume: a source shape with the retail live set (the panel x and y in s1 and s0, the base x and y in s5 and
 * s4, the row counter in s7, the text buffer in s6) so the frame drops to 0x50. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DF00C(s32 panel_x, s32 panel_y) {
    Character* record;
    s32        base_x;
    s32        base_y;
    s32        sprite_x;
    s32        text_x;
    s32        clut;
    s32        row;
    s16        row_y;
    s16        cursor_x;
    s16        cursor_flags;
    u8         index;
    u8         shade;
    u16        value;

    Menu_DrawWindowFrame(panel_x, panel_y, 0x12, 0x15);
    base_x = panel_x + 7;
    base_y = panel_y + 6;
    row    = 0;
    if (D_801E6250 != 0) {
        sprite_x = (panel_x + 0x5D) & HALF_MASK;
        text_x   = (s32)(s16)(panel_x + 0x1F);
        clut     = 0;
        do {
            row_y  = base_y & HALF_MASK;
            record = &g_Characters[g_CharSlot[D_801E6244[row & BYTE_MASK]]];
            UI_DrawWindow(base_x & HALF_MASK, row_y, 125, 48, 0x80, (s32)D_80144952);
            if (text_x != 0) {
                shade = 1;
            } else {
                shade = (u8)((record->status >> 6) & 2);
            }
            index = (u8)(clut & BYTE_MASK);
            Menu_DrawCharacterPortrait((u16)sprite_x, (u16)row_y, record->character_index, shade);
            UI_DrawText((s16)(base_x + 20), (s16)(base_y + 1), (s32)index, 5U, record);
            Menu_DrawIcon((base_x + 2) & HALF_MASK, (s16)(base_y + 0x15) & HALF_MASK, 3U, D_801D0E78);
            sprintf((s8*)g_UiFormatBuffer, &D_801D0E64, record->level);
            UI_DrawGlyphString((s16)text_x, (s16)(base_y + 21), (u32)index, (void*)g_UiFormatBuffer);
            value = record->status;
            if ((value & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
                if (g_FrameCount & 0x20) {
                    cursor_x     = (s16)(base_x + 0x30);
                    cursor_flags = 1;
                    if (index != 0) {
                        cursor_flags = (s16)index;
                    }
                    UI_DrawTextString(cursor_x, (s16)(base_y + 21), (s32)cursor_flags, 0x10, (const u8*)&D_801E5C68);
                } else {
                    cursor_x     = (s16)(base_x + 0x30);
                    cursor_flags = 1;
                    if (index != 0) {
                        cursor_flags = (s16)index;
                    }
                    UI_DrawTextString(cursor_x, (s16)(base_y + 21), (s32)cursor_flags, 0x10, (const u8*)&D_801E5C70);
                }
            } else if (value & STATUS_POISONED) {
                cursor_x     = (s16)(base_x + 0x30);
                cursor_flags = 1;
                if (index != 0) {
                    cursor_flags = (s16)index;
                }
                UI_DrawTextString(cursor_x, (s16)(base_y + 21), (s32)cursor_flags, 0x10, (const u8*)&D_801E5C68);
            } else if (value & 0x20) {
                cursor_x     = (s16)(base_x + 0x30);
                cursor_flags = 1;
                if (index != 0) {
                    cursor_flags = (s16)index;
                }
                UI_DrawTextString(cursor_x, (s16)(base_y + 21), (s32)cursor_flags, 0x10, (const u8*)&D_801E5C70);
            }
            Menu_DrawIcon((base_x + 2) & HALF_MASK, (base_y + 0x1D) & HALF_MASK, 0U, 0U);
            clut = 0;
            if (record->status & STATUS_LOW_HP) {
                clut = 4;
            }
            if (record->current_hp < 2U) {
                clut = 2;
            }
            sprintf((s8*)g_UiFormatBuffer, &D_801D0E68, record->current_hp);
            UI_DrawGlyphString((s16)text_x, (s16)(base_y + 29), (u32)clut, (void*)g_UiFormatBuffer);
            clut = (record->fatigue != 0) * 4;
            sprintf((s8*)g_UiFormatBuffer, &D_801D0E70, record->max_hp);
            UI_DrawGlyphString((s16)text_x, (s16)(base_y + 29), (u32)clut, (void*)g_UiFormatBuffer);
            Menu_DrawIcon((base_x + 2) & HALF_MASK, (base_y + 0x25) & HALF_MASK, 1U, 0U);
            clut  = 0;
            value = record->current_ap;
            if (((u16)(record->max_ap >> 2)) >= value) {
                clut = 4;
            }
            if (value == 0) {
                clut = 2;
            }
            row += 1;
            sprintf((s8*)g_UiFormatBuffer, &D_801D0E68, record->current_ap);
            UI_DrawGlyphString((s16)text_x, (s16)(base_y + 37), (u32)clut, (void*)g_UiFormatBuffer);
            base_y += 0x34;
            sprintf((s8*)g_UiFormatBuffer, &D_801D0E70, record->max_ap);
            UI_DrawGlyphString((s16)text_x, (s16)(base_y + 37), 0U, (void*)g_UiFormatBuffer);
            clut = 0;
        } while ((u32)(row & BYTE_MASK) < (u8)D_801E6250);
    }
}
#else
INCLUDE_ASM(func_801DF00C);
#endif
