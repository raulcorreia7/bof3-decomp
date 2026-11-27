#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F664 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet15(void) {
    g_UIMessageRequest = g_AnswerMessages[30 + g_UIMessageWindow.selection_index];
}
