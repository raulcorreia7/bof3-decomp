#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F664 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage15(void) {
    g_MessageRequest = g_AnswerMessages[30 + g_MessageWindow.selection_index];
}
