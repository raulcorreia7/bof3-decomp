#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F650 row in g_MessageRequest.
 */
MATCH void Message_SetAnswerMessage10(void) {
    g_MessageRequest = g_AnswerMessages[20 + g_MessageWindow.selection_index];
}
