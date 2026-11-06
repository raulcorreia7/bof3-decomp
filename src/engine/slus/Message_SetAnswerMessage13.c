#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F65C row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage13(void) {
    g_MessageRequest = D_8017F628[26 + g_MessageWindow.selection_index];
}
