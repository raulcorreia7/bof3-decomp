#include "battle_15.h"

/* Sprite and palette blocks for the two panel slots. Not declared by headers;
 * the addresses are the binary's own. */

MATCH void func_800B4220(s16 x, s16 y, u8 selected) {
    s16 slot_x;
    u8* style;

    style = &g_WindowStyle;
    UI_WindowDraw((u16)x, (u16)y, 45u, 20u, 0u, *style);
    UI_TextDraw((x + 12), (y + 3), selected != GAME_NONE && selected != 0 ? 7 : 0, MENU_LABEL_LENGTH, (u8*)&s_BattlePanelUseLabel);
    UI_SpriteDrawRun(x, y, selected == 0 ? &s_BattlePanelUnselectedMarker : &s_BattlePanelSelectedMarker, UI_SPRITE_ALT_PAGE);

    slot_x = (x + 0x30);
    UI_WindowDraw((u16)slot_x, (u16)y, 45u, 20u, 0u, *style);
    UI_TextDraw((x + 55), (y + 3), selected != GAME_NONE && selected != 1 ? 7 : 0, MENU_LABEL_LENGTH, (u8*)&s_BattlePanelEquipLabel);
    UI_SpriteDrawRun(slot_x, y, selected == 1 ? &s_BattlePanelUnselectedMarker : &s_BattlePanelSelectedMarker, UI_SPRITE_ALT_PAGE);
}
