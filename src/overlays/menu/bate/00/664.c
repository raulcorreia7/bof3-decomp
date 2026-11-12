#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D1264);

MATCH void func_801D153C(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub2Funcs, D_80148652);
}

MATCH void func_801D1578(void) {
    u8* timer = &D_80148654;
    u8  count;

    Menu_DrawClutStrip(D_80144953);
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_SetMode(UI_MODE_FAST_FADE_OUT);
        D_80148652 += 1;
    }
}

MATCH void func_801D15E4(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80148654 = 0;
        D_80148650 = 1;
        D_80148651 = 0;
        D_80148652 = 0;
        strncpy(&D_80144DE4, &D_801D86F0, 5);
        return;
    }
    Menu_DrawClutStrip(D_80144953);
}

INCLUDE_ASM(func_801D165C);

INCLUDE_ASM(func_801D1AB8);

INCLUDE_ASM(func_801D1C90);

/* Applies the equipment menu's trial set to the record it edits. */
/* func_801D1E8C */
MATCH void Menu_ApplyEquipment(void) {
    u8* slots[EQUIP_SLOT_COUNT];
    u8  item;
    u8  slot;

    slots[EQUIP_SLOT_WEAPON]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.weapon;
    slots[EQUIP_SLOT_SHIELD]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.shield;
    slots[EQUIP_SLOT_HELMET]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.helmet;
    slots[EQUIP_SLOT_ARMOR]       = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.armor;
    slots[EQUIP_SLOT_ACCESSORY_1] = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.accessories[0];
    slots[EQUIP_SLOT_ACCESSORY_2] = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.accessories[1];

    for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++) {
        item = D_801D8ED4.equipped_items[slot];
        if (item == 0) {
            continue;
        }
        if (item == *slots[slot]) {
            continue;
        }
        Item_Remove(D_801D875C[slot], item, 1, 0);
        Item_Add(D_801D875C[slot], *slots[slot], 1, 0);
        *slots[slot] = D_801D8ED4.equipped_items[slot];
    }
    Char_RebuildStats(&g_Characters[MENU_BATE_CHARACTER_RECORD]);
}

MATCH void func_801D1FA0(void) {
    u8 slot;

    slot = D_8014833D;
    if (Item_GetEquipability(D_80148338, slot) & 0x1) {
        D_80148511 = 0;
    } else {
        D_80148511 = 1;
    }
    D_801D8ED4.equipped_items[0]          = D_80144DF2;
    D_801D8ED4.equipped_items[1]          = D_80144DF3;
    D_801D8ED4.equipped_items[2]          = D_80144DF4;
    D_801D8ED4.equipped_items[3]          = D_80144DF5;
    D_801D8ED4.equipped_items[4]          = D_80144DF6;
    /* @bug The trial set stores both accessories to the first accessory slot, so the second keeps its old value. */
    D_801D8ED4.equipped_items[4]          = D_80144DF7;
    D_801D8ED4.equipped_items[D_8014835E] = slot;
}

MATCH void func_801D2070(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep3Funcs, D_80148651);
}

MATCH void func_801D20AC(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep3Sub0Funcs, D_80148652);
}

MATCH void func_801D20E8(void) {
    u8* count;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    count = &D_80148652;
    *count += 1;
}

MATCH void func_801D211C(void) {
    Menu_DrawClutStrip(D_80144953);
    func_801D2304(0x37, 0x37);
    if (g_UiWindowEffectBusy == 0) {
        func_801D259C();
        D_80148658 = 0;
        D_80148652 = 0;
        D_80148651 += 1;
    }
}

INCLUDE_ASM(func_801D2190);

MATCH void func_801D2298(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80148654 = 0;
        D_80148650 = 1;
        D_80148651 = 0;
        D_80148652 = 0;
        return;
    }
    Menu_DrawClutStrip(D_80144953);
    func_801D2304(0x37, 0x37);
}

INCLUDE_ASM(func_801D2304);

MATCH void func_801D259C(void) {
    Character* character;
    u8         i;

    i = 0;
    do {
        D_801D8F00[i] = 0;
        i++;
    } while (i < 6);
    D_801D8EE8[0] = D_801FE4EF;
    D_801D8EE8[1] = D_801FE4E8;
    D_801D8EE8[2] = D_801FE4F0;
    D_801D8EE8[3] = D_801FE4EF;
    D_801D8EE8[4] = D_801FE4E8 / 20;
    if (D_801FE4F0 < 50) {
        D_801D8EE8[5] = 2;
    } else if (D_801FE4F0 - 50 < 30) {
        D_801D8EE8[5] = 4;
    } else if (D_801FE4F0 >= 80) {
        D_801D8EE8[5] = 6;
    }
    character = &g_Characters[MENU_BATE_CHARACTER_RECORD];
    Char_AddStat(&character->base.defense, (s16)D_801D8EE8[3]);
    Char_AddStat(&character->stats.defense, (s16)D_801D8EE8[3]);
    Char_AddCappedStat(&character->base.max_hp, (u16)D_801D8EE8[4]);
    Char_AddCappedStat(&character->stats.max_hp, (u16)D_801D8EE8[4]);
    Char_AddStat(&character->base.power, (s16)D_801D8EE8[5]);
    Char_AddStat(&character->stats.power, (s16)D_801D8EE8[5]);
}

INCLUDE_ASM(func_801D26E0);

INCLUDE_ASM(Menu_DrawCharacterWindow);

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

MATCH void func_801D31B0(s16 x, s16 y, u8 index, u8 flag) {
    Character* character;
    u8*        base;
    u8*        base16;
    u8*        entryp;
    s16        tx;
    s32        pos_x;
    s32        value;
    s32        index_off;
    /* FAKE: retail reserves 24 frame bytes between the outgoing arguments and
     * the saved registers that no statement in the body uses. */
    FAKE_STACK_PADS(u8, 24);

    base = &g_WindowStyle;
    UI_DrawWindow((u16)(x + 3), (u16)(y + 3), MENU_EXPERIENCE_WINDOW_WIDTH, MENU_EXPERIENCE_WINDOW_HEIGHT, 0, base[0]);
    index_off = index * PARTY_RECORD_STRIDE;
    base16    = base + CHARACTER_BLOCK_RECORDS;
    entryp    = base16 + index_off;
    character = (Character*)entryp;
    pos_x     = x;
    tx        = pos_x + MENU_EXPERIENCE_NEXT_X;
    UI_DrawText((flag == 0) ? pos_x + MENU_EXPERIENCE_EXP_X : tx, (s16)(y + MENU_EXPERIENCE_CAPTION_Y), 0, TEXT_LENGTH_MAX, (flag == 0) ? D_801D8B48 : D_801D8B4C);
    if (flag == 0) {
        value = character->exp;
    } else {
        value = Char_GetExpForLevel(index, (character->level + 1) & BYTE_MASK);
    }
    if (value != -1) {
        TEXT_Format(g_UiFormatBuffer, g_MenuExperienceFormat, value);
    } else {
        TEXT_FormatLiteral(g_UiFormatBuffer, g_MenuExperienceBlank);
    }
    UI_DrawAsciiString((s16)(x + MENU_EXPERIENCE_VALUE_X), (s16)(y + MENU_EXPERIENCE_VALUE_Y), 0, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801D8984, 1);
}

#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

#include "overlays/menu/Menu_DrawItemRow.h"

#include "overlays/menu/Menu_DrawEquipment.h"

#include "overlays/menu/Menu_DrawFormationPreview.h"

#include "overlays/menu/Menu_DrawIcon.h"

/* func_801D4678 */
MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#include "overlays/menu/Menu_DrawExperienceLine.h"

#include "overlays/menu/Menu_DrawZennyWindow.h"

#include "overlays/menu/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/Menu_ToggleOption.h"

#include "overlays/menu/Menu_DrawCommandRow.h"

#include "overlays/menu/Item_GetPrice.h"

#include "overlays/menu/Char_GetExpForLevel.h"

#include "overlays/menu/Char_GetExpProgress.h"

INCLUDE_ASM(Menu_DrawHeaderBar);

#include "overlays/menu/Menu_DrawEquipCompareWindow.h"

#include "overlays/menu/Menu_DrawRowIcons.h"

#include "overlays/menu/Menu_DrawEquipStatWindow.h"

const char g_MenuInventoryCountFormat[8] = "%3d/%3d";
const u8   D_801D0D64[4]                 = {0, 0, 0, 0};

#include "overlays/menu/Menu_DrawClutStrip.h"

#include "overlays/menu/Menu_DrawFilledPanel.h"

#include "overlays/menu/Menu_DrawWindowFrame.h"

#include "overlays/menu/Menu_DrawInventoryWindow.h"

/* func_801D73B4 */
#include "overlays/menu/Menu_DrawAbilityList.h"

#include "overlays/menu/Menu_DrawPanelFrame.h"

/* func_801D7AD0 */
#include "overlays/menu/Menu_DrawEquipChoiceWindow.h"

#include "overlays/menu/SAVE_DrawSlotRow.h"

#include "overlays/menu/SAVE_DrawPortTabs.h"
