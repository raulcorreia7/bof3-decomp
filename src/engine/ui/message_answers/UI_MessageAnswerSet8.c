#include "engine/slus/slus.h"

/* stores table entry g_UIMessageChoice of the D_8017F648 row in g_UIMessageRequest.
 */
MATCH void UI_MessageAnswerSet8(void) {
    g_UIMessageRequest = g_AnswerMessages[16 + g_UIMessageWindow.selection_index];
}
