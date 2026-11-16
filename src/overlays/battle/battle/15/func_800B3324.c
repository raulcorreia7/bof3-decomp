#include "battle_15.h"
#include "menu/inventory.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800B3324(u8 index, u16 x, u16 y, s32 patch, s32 hide_changes, MenuPanelTask* task) {
    u8* compare_names[EQUIP_SLOT_COUNT];
    u16 compare_values[4];
    u8  compare_flags[8];

    Character* chr;
    Stats*     stats;
    u8         i;
    s32        icon;
    s32        label_y;
    u16        left;
    u16        top;

    left = x;
    top  = y;
    UI_DrawWindow(x + 4, y + 4, 120, 163, 0, CHARACTER_BLOCK->window_style);
    chr   = (Character*)CHARACTER_BLOCK->records[index];
    stats = &chr->stats;
    UI_DrawText(x + 32, y + 7, 0, 5, chr->name);
    for (i = 0, label_y = y + 26; i < 4; i++) {
        UI_DrawText(x + 5, label_y + i * 13, 0, 4, &g_MenuEquipCompareLabels[i * MENU_EQUIP_STAT_LABEL_SIZE]);
    }
    TEXT_Format(g_UiFormatBuffer, (g_MenuInventoryCountFormat + 8), stats->power);
    UI_DrawGlyphString(left + 49, top + 28, 0, g_UiFormatBuffer);
    TEXT_Format(g_UiFormatBuffer, (g_MenuInventoryCountFormat + 8), stats->defense);
    UI_DrawGlyphString(left + 49, top + 41, 0, g_UiFormatBuffer);
    TEXT_Format(g_UiFormatBuffer, (g_MenuInventoryCountFormat + 8), stats->intelligence);
    UI_DrawGlyphString(left + 49, top + 54, 0, g_UiFormatBuffer);
    TEXT_Format(g_UiFormatBuffer, (g_MenuInventoryCountFormat + 8), stats->agility);
    UI_DrawGlyphString(left + 49, top + 67, 0, g_UiFormatBuffer);

    if (hide_changes == 0) {
        func_80164EF8(index, (u8*)patch, compare_flags, compare_values);
        for (i = 0; i < 4; i++) {
            if (compare_flags[i] == 4) {
                icon = 0x11;
            } else if (compare_flags[i] == 1) {
                icon = 0x12;
            } else {
                icon = 0x13;
            }
            GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
            Menu_DrawPanelIcon(left + 81, top + 26 + i * 13 + 2, icon, 0x1C, GetClut(0, STAGE_PALETTE_Y), GFX_COLOR_NEUTRAL);
            TEXT_Format(g_UiFormatBuffer, (g_MenuInventoryCountFormat + 8), compare_values[i]);
            UI_DrawGlyphString(left + 89, top + 26 + i * 13 + 2, compare_flags[i], g_UiFormatBuffer);
        }
    }

    compare_names[EQUIP_SLOT_WEAPON]      = g_Weapons[chr->equip.weapon].header.name;
    compare_names[EQUIP_SLOT_SHIELD]      = g_Armors[chr->equip.shield].header.name;
    compare_names[EQUIP_SLOT_HELMET]      = g_Armors[chr->equip.helmet].header.name;
    compare_names[EQUIP_SLOT_ARMOR]       = g_Armors[chr->equip.armor].header.name;
    compare_names[EQUIP_SLOT_ACCESSORY_1] = (u8*)g_Accessories[chr->equip.accessories[0]].header.name;
    compare_names[EQUIP_SLOT_ACCESSORY_2] = (u8*)g_Accessories[chr->equip.accessories[1]].header.name;
    for (i = 0; i < EQUIP_SLOT_COUNT; i++) {
        if (i == task->unk_0B) {
            func_801AEA80((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 1);
            UI_DrawText(left + 17, top + 85 + i * 13, MENU_SHADE_DIM, Game_ReadCommand(compare_names[i]) & BYTE_MASK, compare_names[i]);
            func_801AEA80((u16)(left + 6), (u16)(top + i * 13 + 85), g_MenuEquipSlotIcons[i], 0);
            UI_DrawText(left + 17, top + 85 + i * 13 - 2, MENU_SHADE_SELECTED, Game_ReadCommand(compare_names[i]) & BYTE_MASK, compare_names[i]);
        } else if (i == task->unk_0A) {
            func_801AEA80((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 1);
            UI_DrawText(left + 17, top + 85 + i * 13, MENU_SHADE_DIM, Game_ReadCommand(compare_names[i]) & BYTE_MASK, compare_names[i]);
            func_801AEA80((u16)(left + 6), (u16)(top + i * 13 + 85), g_MenuEquipSlotIcons[i], 0);
            UI_DrawText(left + 17, top + 85 + i * 13 - 2, MENU_SHADE_NORMAL, Game_ReadCommand(compare_names[i]) & BYTE_MASK, compare_names[i]);
        } else {
            func_801AEA80((u16)(left + 6), (u16)(top + (i * 13 + 87)), g_MenuEquipSlotIcons[i], 0);
            UI_DrawText(left + 17, top + 85 + i * 13, MENU_SHADE_NORMAL, Game_ReadCommand(compare_names[i]) & BYTE_MASK, compare_names[i]);
        }
    }

    UI_DrawSpriteRun(left, top, g_MenuEquipCompareSprites, 1);
    for (i = 0; i < 7; i++) {
        UI_DrawSprite(left, top + (i + 3) * 8, 4, 1);
        UI_DrawSprite(left + 120, top + (i + 3) * 8, 8, 1);
    }
    for (i = 0; i < 9; i++) {
        UI_DrawSprite(left, top + (i + 11) * 8, 4, 1);
        UI_DrawSprite(left + 120, top + (i + 11) * 8, 8, 1);
    }
    for (i = 0; i < 14; i++) {
        UI_DrawSprite(left + (i + 1) * 8, top + 80, 0xE, 1);
        UI_DrawSprite(left + (i + 1) * 8, top + 160, 0x11, 1);
    }
    UI_DrawSprite(left, top + 80, 0xD, 1);
    UI_DrawSprite(left + 120, top + 80, 0xF, 1);
    UI_DrawSprite(left, top + 160, 0x10, 1);
    UI_DrawSprite(left + 120, top + 160, 0x12, 1);
}
#else
INCLUDE_ASM(func_800B3324);
#endif
