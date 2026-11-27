#include "engine/slus/slus.h"

/* advances the front-end step counter while the pad holds the cue mask, then moves the choice cursor on
 * repeat input: 0x1000 steps back (wrapping to the maximum), 0x4000 forward (wrapping to zero).
 */
MATCH void UI_MessageScrollChoice(void) {
    volatile u16* pad;
    s32           action;
    s8            cursor;

    pad = &g_PadStates[0].pressed;
    if ((*pad & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        u8* step;

        step  = &g_UIMessageStep;
        *step = *step + 1;
    }
    action = INPUT_REPEATED(*pad, (PADLup | PADLdown));
    if ((action & PADLup) != 0) {
        s8* index;

        index  = &g_UIMessageWindow.selection_index;
        cursor = *index - 1;
        *index = cursor;
        if (cursor < 0) {
            *index = g_UIMessageWindow.last_row;
        }
    }
    if ((action & PADLdown) != 0) {
        s8* index;

        index  = &g_UIMessageWindow.selection_index;
        cursor = *index + 1;
        *index = cursor;
        if (g_UIMessageWindow.last_row < cursor) {
            *index = 0;
        }
    }
}
