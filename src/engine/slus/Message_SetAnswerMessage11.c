#include "engine/slus/slus.h"

/* stores table entry g_MessageChoice of the D_8017F654 row in g_MessageRequest. */
MATCH void Message_SetAnswerMessage11(void) {
    g_MessageRequest = g_AnswerMessages[22 + g_MessageWindow.selection_index];
}
