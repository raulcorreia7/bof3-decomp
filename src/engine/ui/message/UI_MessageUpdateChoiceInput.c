#include "engine/slus/slus.h"

/* runs the front-end cue/step handler for the two pad masks: the MENU_INPUT_CANCEL cue sets owner mode 3, arms the
 * area request and steps once; the MENU_INPUT_CONFIRM cue steps twice; otherwise repeat-decoded input moves the choice
 * cursor, wrapping at zero through D_801490C6.
 */
MATCH void UI_MessageUpdateChoiceInput(void) {
    s32 action;

    if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        u8* step;

        g_UIPanelTasks[1].state = 3;
        g_UIPanelTasks[0].state = 1;
        step                    = &g_UIMessageStep;
        *step                   = *step + 1;
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        u8* step;

        step  = &g_UIMessageStep;
        *step = *step + 2;
        return;
    }
    action = INPUT_GetRepeatedButtons(g_PadStates[0].pressed);
    if ((action & PADLup) != 0) {
        u8* index;

        index  = (u8*)&g_UIMessageWindow.selection_index;
        *index = *index - 1;
        if ((s8)*index < 0) {
            *index = g_UIMessageWindow.last_row;
        }
    }
    if ((action & PADLdown) != 0) {
        u8* index;

        index  = (u8*)&g_UIMessageWindow.selection_index;
        *index = *index + 1;
        if (g_UIMessageWindow.last_row < (s8)*index) {
            *index = 0;
        }
    }
}
