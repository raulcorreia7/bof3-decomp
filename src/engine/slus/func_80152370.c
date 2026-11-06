#include "engine/slus/slus.h"

/* stores the D_8017F628 row entry selected by g_MessageChoice in g_MessageRequest and
 * latches the matching mode flag in D_8014865B.
 */
MATCH void func_80152370(void) {
    g_MessageRequest = D_8017F628[g_MessageWindow.selection_index];
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
