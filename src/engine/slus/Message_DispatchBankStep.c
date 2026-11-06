#include "engine/slus/slus.h"

/* copies the handler bank into the local frame, then runs the entry
 * selected by the shared step byte g_MessageWindow.step_id, whose 0x80 base is rebased onto
 * the bank's 16 entries.
 */
MATCH void Message_DispatchBankStep(void) {
    HandlerBank bank;

    bank = g_MessageStepBank;
    bank.handlers[g_MessageWindow.step_id - 0x80]();
}
