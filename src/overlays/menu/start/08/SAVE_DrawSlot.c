#include "start_08.h"

/* Draws one shop row: the window, the row icon and up to three slot icons, the name, two formatted number lines and
 * the value bar; a NULL entry draws only the window. */
MATCH void SAVE_DrawSlot(u8 index, s32 left, s32 top, u8* entry) {
    s16 x;
    s16 y;
    s16 label_x;
    u8  i;
    u8  icon;

    x = left;
    y = top;
    UI_DrawWindow(left + 8, y, 200, 48, 0, D_80144952);
    if (entry != NULL) {
        if (GetGraphType() != 1) {
            GetGraphType();
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, 0xF, NULL);
        GFX_AddPrim(1, 0xC);
        func_801DD618((u16)(left + 9), (u16)(top + 5), (u8)(index + 3), 0x1E, (u16)GetClut(16, 480), 128);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            icon = *(entry + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_DrawText((s16)(x + 21), (s16)(y + 3), 0, 5, entry);
        sprintf((char*)g_UiFormatBuffer, D_801D0DAC, entry[8]);
        UI_DrawGlyphString((s16)(x + 31), (s16)(y + 24), 0, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801D0DB0, entry[0xC], entry[0xD]);
        label_x = x + 0x27;
        UI_DrawGlyphString(label_x, (s16)(y + 37), 0, g_UiFormatBuffer);
        UI_DrawGlyphString(label_x, (s16)(y + 36), 0, D_801D0DBC);
        UI_DrawGlyphString(label_x, (s16)(y + 39), 0, D_801D0DBC);
        func_801DD6D0((u16)(x + 0x14), (u16)(y + 0x12), 0, entry[8], *(s32*)(entry + 0x10));
    }
    UI_DrawSpriteRun((s16)x, (s16)y, D_801EC854, entry[0x14] && entry ? 2 : 0);
    if (entry != NULL && entry[0x14] != 0) {
        UI_DrawSprite((s16)(x + 50), (s16)(y + 22), 0x3D, 0);
    }
}
