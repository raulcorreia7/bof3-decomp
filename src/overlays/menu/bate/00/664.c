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

MATCH void func_801D1E8C(void) {
    u8* slots[6];
    u8* base;
    s32 i;

    base     = &D_80144DF2;
    slots[1] = base + 1;
    slots[2] = base + 2;
    slots[3] = base + 3;
    slots[4] = base + 4;
    slots[0] = base;
    slots[5] = base + 5;

    i = 0;
    do {
        u8 idx  = i;
        u8 item = D_801D8ED4.equipped_items[idx];
        if (item != 0 && item != *slots[idx]) {
            Item_Remove(((u8*)g_MenuBateStep2Sub2Funcs + 0x3C)[idx], item, 1, 0);
            Item_Add(((u8*)g_MenuBateStep2Sub2Funcs + 0x3C)[idx], *slots[idx], 1, 0);
            *slots[idx] = D_801D8ED4.equipped_items[idx];
        }
        i++;
    } while ((u8)i < 6);

    Char_RebuildStats((Character*)&D_80144DE4);
}

MATCH void func_801D1FA0(void) {
    u8 slot;

    slot = D_8014833D;
    if (Item_GetEquipability(D_80148338, slot) & 1) {
        D_80148511 = 0;
    } else {
        D_80148511 = 1;
    }
    D_801D8ED4.equipped_items[0]          = D_80144DF2;
    D_801D8ED4.equipped_items[1]          = D_80144DF3;
    D_801D8ED4.equipped_items[2]          = D_80144DF4;
    D_801D8ED4.equipped_items[3]          = D_80144DF5;
    D_801D8ED4.equipped_items[4]          = D_80144DF6;
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

INCLUDE_ASM(func_801D259C);

INCLUDE_ASM(func_801D26E0);

INCLUDE_ASM(Menu_DrawCharacterWindow);

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

INCLUDE_ASM(func_801D31B0);

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
