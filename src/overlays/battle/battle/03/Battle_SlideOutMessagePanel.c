#include "battle_03.h"

/* func_801EA9FC */
MATCH void Battle_SlideOutMessagePanel(void) {
    s16 y;

    y = g_UIPanelCurrent->pos.vy;
    if (y == -22) {
        D_801EC2E4              = 0;
        g_UIPanelCurrent->state = 0;
    } else {
        g_UIPanelCurrent->pos.vy = y - 8;
    }
    func_801D7EB0(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
    UI_TextDraw((g_UIPanelCurrent->pos.vx + 4), (g_UIPanelCurrent->pos.vy + 3), 0, TEXT_LENGTH_MAX, g_BattleMessages[((D_801EBF04 - 1) & 0xF)].text);
}
