#include "battle_03.h"

/* func_801EAAB8 */
MATCH void Battle_DrawMessagePanel(void) {
    func_801D7EB0(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
    UI_TextDraw((g_UIPanelCurrent->pos.vx + 4u), (g_UIPanelCurrent->pos.vy + 3u), 0, TEXT_LENGTH_MAX, g_BattleMessages[D_801EBF04].text);
}
