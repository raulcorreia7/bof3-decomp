#include "shop_00.h"

/* nonmatching unmeasured: tried the first draft rebuilt on Character and a four-entry flag/value table; first mismatch
 * opcode +0x0, frame 0x50 versus 0x58 and save order; the reviewed jump-table placement also differs while the text
 * differs. resume: parameter locals in the retail s6/s3/s0/s4 order plus the present stack slot, then re-check the
 * jump-table placement. */
/* func_801DB9F0 */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawEquipStatWindow(s32 x, s32 y, u8 character_slot, s32 equip_slot, u8 item_id) {
    Character* stats;
    u8         flags[4];
    u16        values[4];
    u8         present;
    u8         clut;
    u8         category;
    u8         i;

    stats = &g_Characters[character_slot & BYTE_MASK];
    switch (equip_slot & BYTE_MASK) {
        default:
            category = 0;
            break;
        case 1:
            category = 1;
            break;
        case 2:
        case 3:
        case 4:
            category = 2;
            break;
        case 5:
        case 10:
        case 11:
            category = 3;
            break;
    }
    present = ((Item_GetEquipability(category, item_id) >> character_slot) ^ 1) & 1;
    UI_DrawWindow((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, 108, 48, present, D_80144952);
    clut = 0;
    if (present == 0) {
        func_80164D2C(character_slot, (equip_slot - 1) & BYTE_MASK, item_id, flags, values);
        values[2] = values[3];
        flags[2]  = flags[3];
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            sprintf((char*)g_UiFormatBuffer, g_MenuStatFormat, values[i]);
            UI_DrawGlyphString(x + 44, y + i * 15 + 8, flags[i], (void*)g_UiFormatBuffer);
        }
    } else {
        clut = 7;
        sprintf((char*)g_UiFormatBuffer, g_MenuStatFormat, stats->power);
        UI_DrawGlyphString(x + 44, y + 8, 7, (void*)g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, g_MenuStatFormat, stats->defense);
        UI_DrawGlyphString(x + 44, y + 23, 7, (void*)g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, g_MenuStatFormat, stats->agility);
        UI_DrawGlyphString(x + 44, y + 38, 7, (void*)g_UiFormatBuffer);
    }
    Menu_DrawCharacterPortrait((x + 0x46) & HALF_MASK, (y + 2) & HALF_MASK, stats->character_id, present);
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        UI_DrawText(x + 5, y + i * 15 + 6, clut, 0xFF, &D_801E5A10[i * 6]);
    }
    UI_DrawSpriteRun(x, y, D_801E56DC, 0);
}
#else
/* Same body in the shop, start, Bate and Shisu overlays; the shop draft differs from retail in frame size (0x58 against 0x50) and save order, and the retail parameter locals sit in s6, s3, s0 and s4. */
INCLUDE_ASM(Menu_DrawEquipStatWindow);
#endif
