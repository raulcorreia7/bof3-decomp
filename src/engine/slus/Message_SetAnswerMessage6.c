#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the 0x8017F640 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage6(void) {
    g_MessageRequest = D_8017F628[12 + g_MessageWindow.selection_index];
}
