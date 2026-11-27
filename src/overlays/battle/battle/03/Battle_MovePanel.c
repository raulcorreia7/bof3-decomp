#include "battle_03.h"

/* positions the active menu panel from its entry's script offsets and
 * the cursor state, then either reports the hit to the script handler or walks
 * the panel one state down.
 */
/* func_801E9FDC */
MATCH void Battle_MovePanel(void) {
    MenuPanelTask* panel;
    u8             index;
    u8             b0;
    u8             b1;
    u8             flags;

    panel         = g_UIPanelCurrent;
    index         = panel->unk_0A;
    b0            = g_Game.members[index].facing;
    b1            = g_Game.members[index].chr.character_id;
    panel->pos.vx = g_Game.members[index].screen_x.signed_value + *(s8*)&g_BattlePanelOffsets[b1 * 8 + b0 * 2] + (b0 == 0 || b0 == 3 ? D_801EAEA4[0] : D_801EAEA4[2]);

    *(s16*)&g_UIPanelCurrent->pos.vy = g_Game.members[g_UIPanelCurrent->unk_0A].screen_y.value + g_BattlePanelOffsets[b1 * 8 + b0 * 2 + 1] + 12;

    if (g_Battle.selection_latch != 0) {
        flags = g_BattleActorTurn->command.target;
        if ((flags & 0xC0) == 0) {
            if (flags != g_UIPanelCurrent->unk_0A) {
                g_UIPanelCurrent->layer = 0;
                g_UIPanelCurrent->state -= 1;
                return;
            }
        } else if ((flags & 0x80) == 0) {
            g_UIPanelCurrent->layer = 0;
            g_UIPanelCurrent->state -= 1;
            return;
        }
    } else {
        g_UIPanelCurrent->layer = 0;
        g_UIPanelCurrent->state -= 1;
        return;
    }
    func_801D8DF8(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_0A);
}
