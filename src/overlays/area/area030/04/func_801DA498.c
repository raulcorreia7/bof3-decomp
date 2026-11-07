#include "area030_04.h"

/* Scans the table range, bumps the work phase when either mask is
 * set, then calls the shared tail with the second mask. */
MATCH void func_801DA498(void) {
    func_801E19CC(0x44, 0x4E);
    if (g_InputPressed & (g_InputMasks[INPUT_SLOT_CONFIRM] | g_InputMasks[INPUT_SLOT_CANCEL])) {
        FISHING_STATE->sub_index_03 += 1;
    }
    func_801E16DC();
}
