#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F650 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet10(void) {
    g_UiMessageRequest = g_AnswerMessages[20 + g_UiMessageWindow.selection_index];
}
