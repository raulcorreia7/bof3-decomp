#include "engine/slus/slus.h"

/* stores the g_AnswerMessages row entry selected by g_UiMessageChoice in g_UiMessageRequest and
 * latches the matching mode flag in D_8014865B.
 */
MATCH void func_80152370(void) {
    g_UiMessageRequest = g_AnswerMessages[g_UiMessageWindow.selection_index];
    switch (g_UiMessageWindow.selection_index) {
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
