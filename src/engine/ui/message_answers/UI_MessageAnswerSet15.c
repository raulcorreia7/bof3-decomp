#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F664 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet15(void) {
    g_UiMessageRequest = g_AnswerMessages[30 + g_UiMessageWindow.selection_index];
}
