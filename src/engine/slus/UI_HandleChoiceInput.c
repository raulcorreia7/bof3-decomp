#include "engine/slus/slus.h"

/* runs the front-end cue/step handler for the two pad masks: the D_80145AC4 cue sets owner mode 3, arms the
 * area request and steps once; the D_80145AC2 cue steps twice; otherwise repeat-decoded input moves the choice
 * cursor, wrapping at zero through D_801490C6.
 */
MATCH void UI_HandleChoiceInput(void) {
    s32 action;

    if ((g_InputPressed & D_80145AC4) != 0) {
        u8* step;

        D_80148357    = 3;
        D_80148333[0] = 1;
        step          = &g_UiWindowStep;
        *step         = *step + 1;
        return;
    }
    if ((g_InputPressed & D_80145AC2) != 0) {
        u8* step;

        step  = &g_UiWindowStep;
        *step = *step + 2;
        return;
    }
    action = INPUT_GetRepeatedButtons(g_InputPressed);
    if ((action & PADLup) != 0) {
        u8* index;

        index  = (u8*)&D_801490BC.selection_index;
        *index = *index - 1;
        if ((s8)*index < 0) {
            *index = D_801490BC.last_row;
        }
    }
    if ((action & PADLdown) != 0) {
        u8* index;

        index  = (u8*)&D_801490BC.selection_index;
        *index = *index + 1;
        if ((s8)D_801490BC.last_row < (s8)*index) {
            *index = 0;
        }
    }
}
