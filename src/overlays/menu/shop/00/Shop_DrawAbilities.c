#include "shop_00.h"

/* Draws the shop's ability list panel: ten rows with each ability, its level
 * and its func_80166A10 count, the list name, the two cursor tabs and the
 * window frame. */
MATCH void Shop_DrawAbilities(ShopPanel* panel) {
    Ability* ability;
    u8*      list;
    s32      level;
    s32      count;
    s32      locked;
    u8       shade;
    s32      x;
    u16      y;
    u8       flags;
    u8       n;

    UI_DrawWindow((panel->x + 3) & HALF_MASK, (panel->y + 3) & HALF_MASK, 154, 160, 0, CHARACTER_BLOCK->window_style);
    n    = 0;
    list = Party_GetAbilities(panel->unk_0A, panel->unk_0B, 0);
    y    = panel->y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->unk_08, D_80148656, *list) == 0;
            shade  = locked ? 7 : 0;
            if (n == panel->selected) {
                shade = 2;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[D_80144F5A[(s8)D_80148656]], *list, 0);
            if (n == panel->selected || n == panel->unk_0C) {
                if (shade != 7) {
                    func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), 7, (u8)level, ability, (u8)count, 1);
                }
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x18), shade, (u8)level, ability, (u8)count, locked);
            } else {
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), shade, (u8)level, ability, (u8)count, locked);
            }
        }
        n++;
        y += 0xD;
        list++;
    } while (n < 10);
    x = panel->x + 0x4E;
    UI_DrawText((s16)(x - strlen(D_801E5B7C[panel->unk_0B]) * 4), (s16)(panel->y + 7), 0, 0x10,
                (u8*)(D_801E5B7C[panel->unk_0B]));
    UI_DrawSpriteRun(panel->x, panel->y, (panel->flags & 2) ? D_801E5650 : D_801E5638, 1);
    UI_DrawSpriteRun(panel->x, panel->y, (panel->flags & 1) ? D_801E5674 : D_801E5668, 1);
    flags = panel->flags;
    if (!(flags & 0xF0)) {
        panel->flags = 0;
    } else {
        panel->flags = flags - 0x10;
    }
    for (n = 0; n < 10; n++) {
        UI_DrawSprite(panel->x + (n + 5) * 8, panel->y, 1, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x, panel->y + (n + 3) * 8, 4, 1);
    }
    UI_DrawSprite(panel->x + 144, panel->y + 24, 0x20, 1);
    for (n = 0; n < 15; n++) {
        UI_DrawSprite(panel->x + 144, panel->y + (n + 4) * 8, 0x21, 1);
    }
    UI_DrawSprite(panel->x, panel->y + 160, 5, 1);
    UI_DrawSprite(panel->x + 144, panel->y + 152, 0x22, 1);
    if (panel->unk_10 != 0) {
        UI_DrawSprite(panel->x + 8, panel->y, 0x32, 1);
        UI_DrawSprite(panel->x + 144, panel->y, 0x34, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x + (n + 1) * 8, panel->y + 160, 6, 1);
    }
}
