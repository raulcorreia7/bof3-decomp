#include "engine/slus/slus.h"

/* func_80151D3C */
/* Runs the shift handler that the choice step selects. */
MATCH void UI_MessageChoiceShiftRun(void) {
    void (*table[2])(void) = {UI_MessageChoiceShiftBegin, UI_MessageChoiceShiftStep};

    table[g_UIMessageChoiceStep]();
}
