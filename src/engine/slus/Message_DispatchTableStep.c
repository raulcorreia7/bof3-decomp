#include "engine/slus/slus.h"

/* copies the handler table into the local frame. */
MATCH void Message_DispatchTableStep(void) {
    HandlerTable table;

    table = g_MessageStepTable;
    table.handlers[g_MessageWindow.step_id - 0x80]();
}
