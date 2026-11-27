#include "battle_03.h"

/* func_801EA8F4 */
MATCH void Battle_HoldMessagePanel(void) {
    s32 slot;
    u8  value;
    s8  next;

    Battle_DrawMessagePanel();
    if (((g_BattleMessages[D_801EBF04].flags & 0x1) != 0) && (g_PadStates[0].pressed != 0) && ((Battle_AdvanceMessage() & BYTE_MASK) != 0)) {
        g_UIPanelCurrent->state = 3;
    }
    slot = D_801EBF04;
    if ((g_BattleMessages[slot].flags & 0x2) != 0) {
        value = g_BattleMessages[slot].record_type;
        if ((value & BYTE_MASK) != GAME_NONE) {
            next                               = value - 1;
            g_BattleMessages[slot].record_type = next;
            if (((next & BYTE_MASK) == 0) && ((Battle_AdvanceMessage() & BYTE_MASK) != 0)) {
                g_UIPanelCurrent->state = 3;
            }
        }
    }
}
