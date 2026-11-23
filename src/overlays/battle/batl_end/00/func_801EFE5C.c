#include "batl_end_00.h"

/* Draws the level-up result rows: one per stat gain, then the ability rows the next level teaches. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EFE5C(void) {
    s32 y;

    y = 0x2C;
    func_801F039C(0x14, 0x28, 0x118, g_UiPanelCurrent->unk_09);
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 1) != 0) {
        sprintf((char*)g_TextVariables[2], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 1));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 1) == 1 ? 0x7C : 0xC));
        y += 0x10;
    }
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 2) != 0) {
        sprintf((char*)g_TextVariables[3], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 2));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 2) == 1 ? 0x7D : 0xD));
        y += 0x10;
    }
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 3) != 0) {
        sprintf((char*)g_TextVariables[4], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 3));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 3) == 1 ? 0x78 : 8));
        y += 0x10;
    }
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 4) != 0) {
        sprintf((char*)g_TextVariables[5], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 4));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 4) == 1 ? 0x79 : 9));
        y += 0x10;
    }
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 5) != 0) {
        sprintf((char*)g_TextVariables[6], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 5));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 5) == 1 ? 0x7A : 0xA));
        y += 0x10;
    }
    if (func_801EF928(g_UiPanelCurrent->unk_0A, 6) != 0) {
        sprintf((char*)g_TextVariables[7], D_801EEC40, func_801EF928(g_UiPanelCurrent->unk_0A, 6));
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(func_801EF928(g_UiPanelCurrent->unk_0A, 6) == 1 ? 0x7B : 0xB));
        y += 0x10;
    }
    if (g_LevelGrowth[g_UiPanelCurrent->unk_0A][g_UiPanelCurrent->unk_0B].ability != 0) {
        SYS_CopyString(g_TextVariables[8], (u8*)g_Abilities[g_LevelGrowth[g_UiPanelCurrent->unk_0A][g_UiPanelCurrent->unk_0B].ability].name, ABILITY_NAME_LENGTH);
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0x12));
        y += 0x10;
    }
    if (g_LevelGrowth[g_UiPanelCurrent->unk_0A][g_UiPanelCurrent->unk_0B].extra_ability != 0) {
        SYS_CopyString(g_TextVariables[9], (u8*)g_Abilities[g_LevelGrowth[g_UiPanelCurrent->unk_0A][g_UiPanelCurrent->unk_0B].extra_ability].name, ABILITY_NAME_LENGTH);
        UI_TextDraw(0x1E, y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0x13));
    }
}
#else
INCLUDE_ASM(func_801EFE5C);
#endif
