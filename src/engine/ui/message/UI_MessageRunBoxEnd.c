#include "engine/slus/slus.h"

/* Runs the box end step that g_UiMessageStep selects: tick the timer, then confirm. */
MATCH void UI_MessageRunBoxEnd(void) {
    void (*table[2])(void) = {UI_MessageTickBoxEnd, UI_MessageConfirmWhenClosed};

    table[g_UiMessageStep]();
}
