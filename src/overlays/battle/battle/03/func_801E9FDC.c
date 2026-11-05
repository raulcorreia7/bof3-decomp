#include "battle_03.h"

extern s8 D_801EAEA4;

/* positions the active menu panel from its entry's script offsets and
 * the cursor state, then either reports the hit to the script handler or walks
 * the panel one state down.
 */
MATCH void func_801E9FDC(void) {
    MenuPanelTask* panel;
    u8             index;
    u8             b0;
    u8             b1;
    u8             flags;

    panel    = g_MenuPanelTaskCurrent;
    index    = panel->unk_0A;
    b0       = g_BattlePartyBattlers[index].word_08.byte.facing_08;
    b1       = D_80145F09[index][0];
    panel->x = g_BattlePartyBattlers[index].unk_2E.signed_half + *(s8*)&g_BattlePanelOffsets[b1 * 8 + b0 * 2] +
               (b0 == 0 || b0 == 3 ? D_801EAEA4 : D_801EAEA6);

    *(s16*)&g_MenuPanelTaskCurrent->y = g_BattlePartyBattlers[g_MenuPanelTaskCurrent->unk_0A].unk_30.half +
                                        g_BattlePanelOffsets[b1 * 8 + b0 * 2 + 1] + 12;

    if (g_BattleSelectionLatch != 0) {
        flags = *D_801EB4D8;
        if ((flags & 0xC0) == 0) {
            if (flags != g_MenuPanelTaskCurrent->unk_0A) {
                g_MenuPanelTaskCurrent->unk_0F = 0;
                g_MenuPanelTaskCurrent->state -= 1;
                return;
            }
        } else if ((flags & 0x80) == 0) {
            g_MenuPanelTaskCurrent->unk_0F = 0;
            g_MenuPanelTaskCurrent->state -= 1;
            return;
        }
    } else {
        g_MenuPanelTaskCurrent->unk_0F = 0;
        g_MenuPanelTaskCurrent->state -= 1;
        return;
    }
    func_801D8DF8((s16)g_MenuPanelTaskCurrent->x, (s16)g_MenuPanelTaskCurrent->y, g_MenuPanelTaskCurrent->unk_0A);
}
