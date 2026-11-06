#include "engine/slus/slus.h"

/* stores the g_AnswerMessages row entry selected by g_MessageChoice in g_MessageRequest and
 * latches the matching mode flag in D_8014865B.
 */
MATCH void func_80152370(void) {
    g_MessageRequest = g_AnswerMessages[g_MessageWindow.selection_index];
    switch (g_MessageWindow.selection_index) {
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
