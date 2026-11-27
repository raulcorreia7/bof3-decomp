#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F654 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet11(void) {
    g_UIMessageRequest = g_AnswerMessages[22 + g_UIMessageWindow.selection_index];
}
