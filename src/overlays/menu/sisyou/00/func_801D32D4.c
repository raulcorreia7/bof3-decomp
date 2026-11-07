#include "sisyou_00.h"

/* Sub-handler table of sisyou step 4 (g_MasterMenuStates[4] is func_801D32D4); the
 * sub-step byte g_MasterSubStep selects the entry. */

MATCH void func_801D32D4(void) {
    SYS_DISPATCH_BYTE(g_MasterStep4Funcs, g_MasterSubStep);
}
