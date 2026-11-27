#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F660 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet14(void) {
    g_UIMessageRequest = g_AnswerMessages[28 + g_UIMessageWindow.selection_index];
}
