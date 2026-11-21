#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F658 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet12(void) {
    g_UiMessageRequest = g_AnswerMessages[24 + g_UiMessageWindow.selection_index];
}
