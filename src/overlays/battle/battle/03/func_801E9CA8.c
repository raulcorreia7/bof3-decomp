#include "battle_03.h"

/* loads the active menu panel's gauge fraction and caps for both
 * bars from its entry, clamping each to one, and advances the panel.
 */
MATCH void func_801E9CA8(void) {
    MenuPanelTask* p1;
    MenuPanelTask* p2;
    MenuPanelTask* p3;
    MenuPanelTask* p4;
    u32            slot;

    p1         = g_MenuCurrentPanel;
    p1->unk_0B = (g_BattlePartyBattlers[p1->unk_0A].stats.current_hp * 0x37) /
                 g_BattlePartyBattlers[p1->unk_0A].stats.stats.max_hp;
    p2         = g_MenuCurrentPanel;
    slot       = p2->unk_0A;
    if (g_BattlePartyBattlers[slot].stats.current_hp != 0) {
        if (p2->unk_0B == 0) {
            p2->unk_0B = 1;
            p2         = g_MenuCurrentPanel;
            slot       = p2->unk_0A;
        }
    }
    p2->unk_14 = g_BattlePartyBattlers[slot].stats.current_hp;
    p2->unk_1C = g_BattlePartyBattlers[p2->unk_0A].stats.stats.max_hp;
    p2->flags  = 0;
    p3         = g_MenuCurrentPanel;
    slot       = p3->unk_0A;
    if (g_BattlePartyBattlers[slot].stats.stats.max_ap != 0) {
        p3->unk_0C =
            (g_BattlePartyBattlers[slot].stats.current_ap * 0x37) / g_BattlePartyBattlers[slot].stats.stats.max_ap;
        p4   = g_MenuCurrentPanel;
        slot = p4->unk_0A;
        if (g_BattlePartyBattlers[slot].stats.current_ap != 0) {
            if (p4->unk_0C == 0) {
                p4->unk_0C = 1;
            }
        }
    } else {
        p3->unk_0C = 0;
    }
    p4         = g_MenuCurrentPanel;
    slot       = p4->unk_0A;
    p4->unk_16 = g_BattlePartyBattlers[slot].stats.current_ap;
    p4->unk_1E = g_BattlePartyBattlers[p4->unk_0A].stats.stats.max_ap;
    p4->unk_0E = 0;
    g_MenuCurrentPanel->state += 1;
}
