#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F660 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage14(void) {
    g_MessageRequest = g_AnswerMessages[28 + g_MessageWindow.selection_index];
}
