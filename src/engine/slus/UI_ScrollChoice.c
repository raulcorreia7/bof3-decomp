#include "engine/slus/slus.h"

/* advances the front-end step counter while the pad holds the cue mask. */
MATCH void UI_ScrollChoice(void) {
    volatile u16* pad;
    s32           action;
    s8            cursor;

    pad = &g_InputPressed;
    if ((*pad & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        u8* step;

        step  = &g_UiWindowStep;
        *step = *step + 1;
    }
    action = INPUT_REPEATED(*pad, (PADLup | PADLdown));
    if ((action & PADLup) != 0) {
        s8* index;

        index  = &g_MessageWindow.selection_index;
        cursor = *index - 1;
        *index = cursor;
        if (cursor < 0) {
            *index = g_MessageWindow.last_row;
        }
    }
    if ((action & PADLdown) != 0) {
        s8* index;

        index  = &g_MessageWindow.selection_index;
        cursor = *index + 1;
        *index = cursor;
        if (g_MessageWindow.last_row < cursor) {
            *index = 0;
        }
    }
}
