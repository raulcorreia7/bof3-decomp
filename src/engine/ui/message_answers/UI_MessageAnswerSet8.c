#include "engine/slus/slus.h"

/* stores table entry g_UiMessageChoice of the D_8017F648 row in g_UiMessageRequest.
 */
MATCH void UI_MessageAnswerSet8(void) {
    g_UiMessageRequest = g_AnswerMessages[16 + g_UiMessageWindow.selection_index];
}
