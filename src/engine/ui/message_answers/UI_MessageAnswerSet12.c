#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F658 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet12(void) {
    g_UIMessageRequest = g_AnswerMessages[24 + g_UIMessageWindow.selection_index];
}
