#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F65C row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet13(void) {
    g_UiMessageRequest = g_AnswerMessages[26 + g_UiMessageWindow.selection_index];
}
