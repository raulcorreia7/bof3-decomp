#include "area030_04.h"

/* Draws the area-030 accessory rows: the accessory icons of every
 * slot with their count text and the frame behind them. */
/* RESIDUAL: 47.01%; retail frame 0x78, current frame 0x70, and the
 * call sequence differ. FISHING_STATE->y_38.half.slot_3A is the typed s16 at
 * offset 0x3A. resume: reproduce the retail control-flow and frame shape. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8364(s16 panel_x, s16 panel_y) {
    s16 bar_x;
    s16 bar_y;
    s16 text_x;
    s16 text_y;
    s16 row_y;
    s16 offset_y;
    s32 slot;
    s32 row;
    s32 index;
    s32 count;
    u8  max_count;
    u8  max_rows;
    u8  accessory;
    u8* cursor;
    u8* text;

    UI_DrawWindow(panel_x, (panel_y + 1) & HALF_MASK, 0x8B, 0x9E, 0x80, (s32)g_WindowStyle);
    if (FISHING_STATE->step_index_0A != 0) {
        FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A - 1);
        max_count                    = 0xA;
        max_rows                     = (u8)(FISHING_STATE->y_38.pos_y - 1);
        if (FISHING_STATE->counter_08 != 0) {
            offset_y = (s16)(0x19 - (FISHING_STATE->step_index_0A * 4));
        } else {
            offset_y = (s16)(0x19 - ((3 - FISHING_STATE->step_index_0A) * 4));
        }
    } else {
        max_count = 9;
        max_rows  = FISHING_STATE->y_38.pos_y;
        offset_y  = 0x19;
    }
    slot   = 0;
    row    = 0;
    index  = 0;
    text   = g_UiFormatBuffer;
    cursor = g_InventoryIds[3];
    bar_x  = (s16)(panel_x + 5);
    text_y = 0;
    row_y  = -2;
    do {
        accessory = *cursor;
        if (g_Accessories[accessory].kind == 0xA) {
            if ((row >= (s32)max_rows) && (index < (s32)max_count)) {
                if (*D_80145E94 == 2) {
                    if (FISHING_STATE->counter_07 & 1) {
                        if (FISHING_STATE->step_14 == index) {
                            UI_DrawText(bar_x, bar_y, 7, 0xCU, (&g_Accessories[accessory]));
                            UI_DrawText(bar_x, (s16)(text_y + row_y), 0, 0xCU, (&g_Accessories[*cursor]));
                            if (g_InventoryCounts[3][slot] >= 2U) {
                                sprintf((s8*)text, D_801D0C14, g_InventoryCounts[3][slot]);
                                text_x = (s16)(panel_x + 0x68);
                                UI_DrawGlyphString(text_x, (s16)(text_y + (row_y + 4)), 7U, text);
                                goto drawn; /* joins the shared count-text draw */
                            }
                        }
                    }
                }
                UI_DrawText(bar_x, bar_y, 0, 0xCU, (&g_Accessories[*cursor]));
                if (g_InventoryCounts[3][slot] >= 2U) {
                    sprintf((s8*)text, D_801D0C14, g_InventoryCounts[3][slot]);
                    text_x = (s16)(panel_x + 0x68);
                    UI_DrawGlyphString(text_x, (s16)(text_y + (row_y + 2)), 0U, text);
                }
            drawn: /* the count text is drawn once, from either path */
                if (FISHING_STATE->step_14 == index) {
                    FISHING_STATE->y_38.half.slot_3A = (s16)slot;
                }
                bar_y += 0xD;
                row_y += 0xD;
                index += 1;
            }
            row += 1;
        }
        slot += 1;
        cursor += 1;
    } while (slot < 128);
    FISHING_STATE->unk_1C = row - 1;
    if (FISHING_STATE->step_14 >= index) {
        if ((row - 1 != 0) && (index != 0)) {
            FISHING_STATE->step_14 = index - 1;
        } else {
            FISHING_STATE->step_14 = 0;
        }
    }
    func_801D90FC((s32)panel_x, panel_y);
    count = 0;
    do {
        if (g_Accessories[g_InventoryIds[3][count]].kind == 0xA) {
            index += 1;
        }
        count += 1;
    } while (count < 128);
    if (index < 10) {
        text_y = 0x1C;
    } else {
        index -= 9;
        text_y = (s16)(0x72 - (index * 6));
        if (FISHING_STATE->step_index_0A != 0) {
            if (FISHING_STATE->counter_08 != 0) {
                text_y = (s16)(text_y + (FISHING_STATE->step_index_0A * 2));
            } else {
                text_y = (s16)(text_y - (FISHING_STATE->step_index_0A * 2));
            }
        }
    }
    func_801D8248((s16)(panel_x + 0x80), (s16)(panel_y + (text_y & BYTE_MASK)), 0x72 & 0xFE);
    UI_DrawText((s16)(panel_x + 0x37), (s16)(panel_y + 7), 0, 4U, (&D_801E21D0));
}
#else
INCLUDE_ASM(func_801D8364);
#endif
