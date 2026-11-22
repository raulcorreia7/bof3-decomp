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
    func_801DE9A8((g_Battle.selection - 1) & BYTE_MASK);
    *(u16*)&g_Battle.unk_D0[2] = g_Characters[g_Battle.cursor.gene.column].level;
    *(u16*)&g_Battle.unk_D0[4] = g_Characters[g_Battle.cursor.gene.column].level + func_801EF928(g_Battle.cursor.gene.column, 0);
    sprintf((char*)D_801490F8, D_801EEC04, *(u16*)&g_Battle.unk_D0[4]);
    g_BattleEventSlots[0].payload = UI_MessageGetText(7);
    for (i = 1; i < 7; i++) {
        if (func_801EF928(g_Battle.cursor.gene.column, (u8)i) != 0) {
            height += 0x10;
        }
    }
    if (g_LevelGrowth[g_Battle.cursor.gene.column][*(u16*)&g_Battle.unk_D0[2]].ability != 0) {
        height += 0x10;
    }
    if (g_LevelGrowth[g_Battle.cursor.gene.column][*(u16*)&g_Battle.unk_D0[2]].extra_ability != 0) {
        height += 0x10;
    }
    UI_PanelOpenTask(1, 4);
    D_80148356 = 0;
    D_80148357 = 0;
    D_8014835D = height + 4;
    FAKE_BARRIER();
    D_8014835E = g_Battle.cursor.gene.column;
    D_8014835F = *(u16*)&g_Battle.unk_D0[2];
    g_Battle.ui_mode -= 1;
}
#else
INCLUDE_ASM(func_801EF140);
#endif
