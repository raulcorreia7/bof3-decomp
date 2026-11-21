#include "batl_end_00.h"

/* Opens the victory level-up panel for the character the battle cursor points at: counts the
 * stat rows the level-ups add and the ability rows the next level teaches, then sizes the panel.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801EF140(void) {
    u16 i;
    s32 height;

    height = 0;
    if (g_PadStates[0].pressed == 0) {
        return;
    }
    func_801DE9A8((g_Battle.row_cursor - 1) & BYTE_MASK);
    D_801463B2 = g_Characters[g_Battle.cursor.gene.column].level;
    D_801463B4 = g_Characters[g_Battle.cursor.gene.column].level + func_801EF928(g_Battle.cursor.gene.column, 0);
    sprintf((char*)D_801490F8, D_801EEC04, D_801463B4);
    D_801EB4F4 = Message_GetText(7);
    for (i = 1; i < 7; i++) {
        if (func_801EF928(g_Battle.cursor.gene.column, (u8)i) != 0) {
            height += 0x10;
        }
    }
    if (g_LevelGrowth[g_Battle.cursor.gene.column][D_801463B2].ability != 0) {
        height += 0x10;
    }
    if (g_LevelGrowth[g_Battle.cursor.gene.column][D_801463B2].extra_ability != 0) {
        height += 0x10;
    }
    Menu_OpenPanelTask(1, 4);
    D_80148356 = 0;
    D_80148357 = 0;
    D_8014835D = height + 4;
    D_8014835E = g_Battle.cursor.gene.column;
    D_8014835F = D_801463B2;
    g_Battle.ui_mode -= 1;
}
#else
INCLUDE_ASM(func_801EF140);
#endif
