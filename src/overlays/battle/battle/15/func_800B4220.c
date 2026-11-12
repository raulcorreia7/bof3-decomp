#include "battle_15.h"

/* Sprite and palette blocks for the two panel slots. Not declared by headers;
 * the addresses are the binary's own. */

MATCH void func_800B4220(s16 x, s16 y, u8 selected) {
    s16 slot_x;
    u8* style;

    style = &g_WindowStyle;
    UI_DrawWindow((u16)x, (u16)y, 45u, 20u, 0u, *style);
    UI_DrawText((x + 12), (y + 3), selected != GAME_NONE && selected != 0 ? 7 : 0, 16u, (u8*)&s_BattlePanelUseLabel);
    UI_DrawSpriteRun(x, y, selected == 0 ? &s_BattlePanelUnselectedMarker : &s_BattlePanelSelectedMarker, 1u);

    slot_x = (x + 0x30);
    UI_DrawWindow((u16)slot_x, (u16)y, 45u, 20u, 0u, *style);
    UI_DrawText((x + 55), (y + 3), selected != GAME_NONE && selected != 1 ? 7 : 0, 16u, (u8*)&s_BattlePanelEquipLabel);
    UI_DrawSpriteRun(slot_x, y, selected == 1 ? &s_BattlePanelUnselectedMarker : &s_BattlePanelSelectedMarker, 1u);
}
