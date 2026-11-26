#include "engine/slus/slus.h"

/* Runs the page step that g_UiMessageStep selects: wait for input, then the phase ticker. */
MATCH void UI_MessageRunPage(void) {
    void (*table[2])(void) = {UI_MessageWaitInput, func_8015102C};

    table[g_UiMessageStep]();
}
