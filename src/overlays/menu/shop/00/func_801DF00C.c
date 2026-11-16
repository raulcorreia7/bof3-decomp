#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DF00C(s32 x, s32 y) {
    Character* record;
    s32        base_x;
    s32        base_y;
    u8         row;
    u8         highlight;
    u8         clut;
    u8         flags;
    s32        text_x;
    s32        sprite_x;
    u32        row_y;
    u8         index;
    u8         shade;

    Menu_DrawWindowFrame(x, y, 0x12, 0x15);
    base_x = x + 7;
    base_y = y + 6;
    if (D_801E6250 == 0) {
        return;
    }
    highlight = 0;
    row       = 0;
    sprite_x  = (x + 0x5D) & HALF_MASK;
    text_x    = x + 0x1F;
    do {
        clut   = 0;
        row_y  = base_y & HALF_MASK;
        record = &g_Characters[g_CharSlot[D_801E6244[row & BYTE_MASK]]];
        UI_DrawWindow(base_x & HALF_MASK, row_y, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, 0x80, g_WindowStyle);
        if (highlight != 0) {
            shade = 1;
        } else {
            shade = (record->status >> 6) & 2;
        }
        index = clut;
        Menu_DrawCharacterPortrait(sprite_x, row_y, record->character_id, shade);
        UI_DrawText((s16)(base_x + 20), (s16)(base_y + 1), index, 5U, record);
        Menu_DrawIcon((base_x + 2) & HALF_MASK, (base_y + 0x15) & HALF_MASK, 3U, D_801D0E78[0]);
        TEXT_Format(g_UiFormatBuffer, D_801D0E64, record->level);
        UI_DrawGlyphString((s16)text_x, (s16)(base_y + 0x15), index, g_UiFormatBuffer);
        if ((record->status & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
            if (g_FrameCount & 0x20) {
                flags = 1;
                if (index != 0) {
                    flags = index;
                }
                UI_DrawTextString((s16)(base_x + 0x30), (s16)(base_y + 0x15), flags, 0x10, D_801E5C68);
            } else {
                flags = 1;
                if (index != 0) {
                    flags = index;
                }
                UI_DrawTextString((s16)(base_x + 0x30), (s16)(base_y + 0x15), flags, 0x10, D_801E5C70);
            }
        } else if (record->status & STATUS_POISONED) {
            flags = 1;
            if (index != 0) {
                flags = index;
            }
            UI_DrawTextString((s16)(base_x + 0x30), (s16)(base_y + 0x15), flags, 0x10, D_801E5C68);
        } else if (record->status & STATUS_CONFUSED) {
            flags = 1;
            if (index != 0) {
                flags = index;
            }
            UI_DrawTextString((s16)(base_x + 0x30), (s16)(base_y + 0x15), flags, 0x10, D_801E5C70);
        }
        Menu_DrawIcon((base_x + 2) & HALF_MASK, (base_y + 0x1D) & HALF_MASK, 0U, 0U);
        if (highlight != 0) {
            clut = 7;
        } else {
            if (record->status & STATUS_LOW_HP) {
                clut = 4;
            }
            if (record->hp < 2U) {
                clut = 2;
            }
        }
        TEXT_Format(g_UiFormatBuffer, D_801D0E68, record->hp);
        UI_DrawGlyphString((s16)text_x, (s16)(base_y + 0x1D), clut, g_UiFormatBuffer);
        if (highlight != 0) {
            clut = 7;
        } else {
            clut = (record->fatigue != 0) * 4;
        }
        TEXT_Format(g_UiFormatBuffer, D_801D0E70, record->stats.max_hp);
        UI_DrawGlyphString((s16)text_x, (s16)(base_y + 0x1D), clut, g_UiFormatBuffer);
        Menu_DrawIcon((base_x + 2) & HALF_MASK, (base_y + 0x25) & HALF_MASK, 1U, 0U);
        clut = 0;
        if (highlight != 0) {
            clut = 7;
        } else {
            if ((u16)(record->stats.max_ap >> 2) >= record->ap) {
                clut = 4;
            }
            if (record->ap == 0) {
                clut = 2;
            }
        }
        TEXT_Format(g_UiFormatBuffer, D_801D0E68, record->ap);
        row += 1;
        UI_DrawGlyphString((s16)text_x, (s16)(base_y + 0x25), clut, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, D_801D0E70, record->stats.max_ap);
        UI_DrawGlyphString((s16)text_x, (s16)(base_y + 0x25), 0U, g_UiFormatBuffer);
        base_y += 0x34;
    } while ((u32)(row & BYTE_MASK) < D_801E6250);
}
#else
INCLUDE_ASM(func_801DF00C);
#endif
