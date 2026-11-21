#include "engine/slus/slus.h"

/* copies the handler table into the local frame, then runs the entry
 * selected by the shared step byte g_UiMessageWindow.step_id, whose 0x80 base is rebased onto
 * the table's 16 entries.
 */
MATCH void UI_MessageDispatchStep(void) {
    MessageSteps table;

    table = g_UiMessageSteps;
    table.steps[g_UiMessageWindow.step_id - 0x80]();
}
