#include "battle_03.h"

/* The entrance row table. Each row holds the sprite pair's byte offsets. */

/* primes the battle entrance row state, then steps each of the seven
 * entrance rows through its handler and its entrance sprite pair.
 */
/* func_801D238C */
MATCH void Battle_DrawEntrances(void) {
    u8 panel_index;

    if ((g_PadStates[0].held & PADselect) == 0) {
        /* FAKE: the address-held counter; `g_Battle.phase.sub_step += 1` scores 93.44%. */
        u8* count;

        count                   = &g_Battle.phase.sub_step;
        g_UIPanelTasks[2].state = 1;
        g_UIPanelTasks[1].state = 1;
        g_UIPanelTasks[3].state = 1;
        (*count)++;
    }
    Battle_DrawPartyPanel(g_UIPanelTasks[1].pos.vx, g_UIPanelTasks[1].pos.vy);
    Battle_DrawDimOverlay();
    for (panel_index = 0; panel_index < 7; panel_index++) {
        func_801D8450(panel_index);
        UI_IconDrawCell(panel_index, s_BattlePanelOffsets[panel_index][0] + 0x88, s_BattlePanelOffsets[panel_index][1] + 0x58, BATTLE_PANEL_SIZE, BATTLE_PANEL_SIZE, GFX_COLOR_NEUTRAL);
    }
}
