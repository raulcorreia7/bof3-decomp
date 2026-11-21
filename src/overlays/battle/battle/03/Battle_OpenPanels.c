#include "battle_03.h"

/* Reserves the battle stage's selection panel entries and fills one ring record per active battler
 * from its stage tables.
 */
/* func_801D1828 */
MATCH void Battle_OpenPanels(void) {
    u8* group;
    u8  slot;
    u8  battler;
    u8  first;
    u8* counter;
    s32 index;
    s16 panel_x;
    s16 panel_y;

    D_801EBF04               = 0;
    D_801EC328               = 0;
    slot                     = UI_PanelOpenTask(0x14, 3) & BYTE_MASK;
    D_80148332[slot].mode_00 = 7;
    D_80148332[slot].x_02    = 0x14;
    D_80148332[slot].unk_01  = 0;
    D_80148332[slot].y_04    = -0x16;
    group                    = &g_Battle.outcome.surprise;
    if (*group == 1) {
        Battle_AddMessage(2, 0x30, UI_MessageGetText(BATTLE_TEXT_INITIATIVE_PARTY));
    }
    if (*group == 2) {
        Battle_AddMessage(2, 0x30, UI_MessageGetText(BATTLE_TEXT_INITIATIVE_OPPONENT));
    }
    for (battler = 0; battler < BATTLE_PARTY_CHARACTERS_COUNT; battler++) {
        if (ACTOR_IN_USE(g_Game.members[battler])) {
            UI_PanelOpenTask((battler + MENU_PANEL_BATTLER_FIRST) & BYTE_MASK, 3);
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].mode_00 = 5;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].unk_01  = 0;
            first                                                  = g_Game.members[battler].facing;
            index                                                  = first * CHAR_ID_GARR + g_Game.members[battler].chr.character_id * 8;
            panel_x                                                = g_Game.members[battler].screen_x.value + g_BattlePanelOffsets[index];
            panel_x                                                = D_801EAEA4[(g_Battle.scroll_dir & 0xFE) ^ 0x2] + panel_x;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].x_02    = panel_x;
            /* The y lookup reloads the row bytes; the x store may have changed them. */
            index                                                  = g_Game.members[battler].facing * CHAR_ID_GARR + g_Game.members[battler].chr.character_id * 8;
            panel_y                                                = g_Game.members[battler].screen_y.value + (g_BattlePanelOffsets + 1)[index] + 0xC;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].battler = battler;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].unk_06  = 0;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].unk_07  = 0;
            D_80148332[MENU_PANEL_BATTLER_FIRST + battler].y_04    = panel_y;
        }
    }
    Battle_OpenPartyPanel(0);
    func_800AC964();
    counter = &g_Battle.phase.sub_step;
    *counter += 1;
}
