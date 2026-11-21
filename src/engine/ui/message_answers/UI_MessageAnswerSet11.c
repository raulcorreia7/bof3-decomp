#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F654 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet11(void) {
    g_UiMessageRequest = g_AnswerMessages[22 + g_UiMessageWindow.selection_index];
}
