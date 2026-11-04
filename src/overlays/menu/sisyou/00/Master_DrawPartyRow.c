#include "sisyou_00.h"

MATCH void Master_DrawPartyRow(u16 x, u16 y, u8 entry, u8 icon) {
    Character* record;
    u8*        base;
    s16        text_x;
    s16        text_y;
    u32        value;
    s32        align;

    base = &D_80144952;
    UI_DrawWindow((u16)(x + 3), (u16)(y + 3), 125, 48, 0, base[0]);
    /* FAKE: the record base is formed straight from the byte symbol; folding the offset through the pointer local
     * places the address pair too early. */
    record = (Character*)(&D_80144952 + 0x16) + entry;
    Menu_DrawPortrait((u16)(x + 0x56), (u16)(y + 2), record->character_id, (u8)((record->status >> 6) & 2));
    UI_DrawText((s16)(x + 20), (s16)(y + 3), 0, 5, (u8*)record);
    sprintf((char*)g_UiFormatBuffer, D_801D0C04, record->level);
    UI_DrawGlyphString((s16)(x + 22), (s16)(y + 23), 0, g_UiFormatBuffer);

    if ((STATUS_WORD(record) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString((s16)(x + 46), (s16)(y + 23), 1, 0x10, D_801D4048);
        } else {
            UI_DrawTextString((s16)(x + 46), (s16)(y + 23), 1, 0x10, D_801D4050);
        }
    } else if (record->status & STATUS_POISONED) {
        UI_DrawTextString((s16)(x + 46), (s16)(y + 23), 1, 0x10, D_801D4048);
    } else if (record->status & 0x20) {
        UI_DrawTextString((s16)(x + 46), (s16)(y + 23), 1, 0x10, D_801D4050);
    }

    value = record->current_hp;
    align = (record->status >> 11) & 4;
    if (value < 2U) {
        align = 2;
    }
    sprintf((char*)g_UiFormatBuffer, D_801D0C08, value);
    text_x = (s16)(x + 0x16);
    text_y = (s16)(y + 0x1F);
    UI_DrawGlyphString(text_x, text_y, align, g_UiFormatBuffer);
    sprintf((char*)g_UiFormatBuffer, D_801D0C10, record->max_hp);
    UI_DrawGlyphString(text_x, text_y, 0, g_UiFormatBuffer);

    align = ((record->max_ap >> 2) >= record->current_ap) ? 4 : 0;
    if (record->current_ap == 0) {
        align = 2;
    }
    sprintf((char*)g_UiFormatBuffer, D_801D0C08, record->current_ap);
    text_y = (s16)(y + 0x27);
    UI_DrawGlyphString(text_x, text_y, align, g_UiFormatBuffer);
    sprintf((char*)g_UiFormatBuffer, D_801D0C10, record->max_ap);
    UI_DrawGlyphString(text_x, text_y, 0, g_UiFormatBuffer);

    UI_DrawSpriteRun(x, y, D_801D3F58, 0);
    Menu_DrawExperienceLine((u16)(x + 0x14), (u16)(y + 0x12), entry, record->level, record->exp);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, 0xF, 0);
    GFX_AddPrim(1, 0xC);
    Menu_DrawIcon((u16)(x + 9), (u16)(y + 5), (u8)(icon + 3), 0x1E, GetClut(16, 480), 128);
}
