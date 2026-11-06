#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F658 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage12(void) {
    g_MessageRequest = g_AnswerMessages[24 + g_MessageWindow.selection_index];
}
