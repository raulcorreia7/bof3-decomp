#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the 0x8017F63C row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet5(void) {
    g_UiMessageRequest = g_AnswerMessages[10 + g_UiMessageWindow.selection_index];
}
