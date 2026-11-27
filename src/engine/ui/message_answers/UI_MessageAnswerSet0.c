#include "engine/slus/slus.h"

/* func_80152370 */
/* Stores the answer message of choice slot 0 (row 0) and latches the mode flag for choice 0 or 1. */
MATCH void UI_MessageAnswerSet0(void) {
    g_UIMessageRequest = g_AnswerMessages[g_UIMessageWindow.selection_index];
    switch (g_UIMessageWindow.selection_index) {
        case 0:
            D_8014865B = 1;
            break;
        case 1:
            D_8014865B = 0;
            break;
        default:
            break;
    }
}
