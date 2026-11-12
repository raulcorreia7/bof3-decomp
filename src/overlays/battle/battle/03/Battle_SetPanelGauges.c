#include "battle_03.h"

/* loads the active menu panel's gauge fraction and caps for both
 * bars from its entry, clamping each to one, and advances the panel.
 */
/* func_801E9CA8 */
MATCH void Battle_SetPanelGauges(void) {
    MenuPanelTask* p1;
    MenuPanelTask* p2;
    MenuPanelTask* p3;
    MenuPanelTask* p4;
    u32            slot;

    p1         = g_MenuCurrentPanel;
    p1->unk_0B = (g_Game.members[p1->unk_0A].chr.hp * 0x37) / g_Game.members[p1->unk_0A].chr.stats.max_hp;
    p2         = g_MenuCurrentPanel;
    slot       = p2->unk_0A;
    if (g_Game.members[slot].chr.hp != 0) {
        if (p2->unk_0B == 0) {
            p2->unk_0B = 1;
            p2         = g_MenuCurrentPanel;
            slot       = p2->unk_0A;
        }
    }
    p2->u.battle.hp     = g_Game.members[slot].chr.hp;
    p2->u.battle.max_hp = g_Game.members[p2->unk_0A].chr.stats.max_hp;
    p2->flags           = 0;
    p3                  = g_MenuCurrentPanel;
    slot                = p3->unk_0A;
    if (g_Game.members[slot].chr.stats.max_ap != 0) {
        p3->unk_0C = (g_Game.members[slot].chr.ap * 0x37) / g_Game.members[slot].chr.stats.max_ap;
        p4         = g_MenuCurrentPanel;
        slot       = p4->unk_0A;
        if (g_Game.members[slot].chr.ap != 0) {
            if (p4->unk_0C == 0) {
                p4->unk_0C = 1;
            }
        }
    } else {
        p3->unk_0C = 0;
    }
    p4                  = g_MenuCurrentPanel;
    slot                = p4->unk_0A;
    p4->u.battle.ap     = g_Game.members[slot].chr.ap;
    p4->u.battle.max_ap = g_Game.members[p4->unk_0A].chr.stats.max_ap;
    p4->unk_0E          = 0;
    g_MenuCurrentPanel->state += 1;
}
