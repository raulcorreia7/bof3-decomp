#include "engine/slus/slus.h"

/* Runs the message end step that g_UiMessageStep selects: wait for input, then confirm. */
MATCH void UI_MessageRunEnd(void) {
    void (*table[2])(void) = {UI_MessageWaitEndInput, UI_MessageConfirmWhenClosed};

    table[g_UiMessageStep]();
}
