#include "engine/slus/slus.h"

/* Requests the answer message the selection picks from the D_8017F658 row. */
MATCH void UI_MessageAnswerSet12(void) {
    g_UIMessageRequest = g_AnswerMessages[24 + g_UIMessageWindow.selection_index];
}
