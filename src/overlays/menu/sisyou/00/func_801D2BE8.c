#include "sisyou_00.h"

/* Sub-handler table of sisyou step 3 (g_MasterMenuStates[3] is func_801D2BE8); the
 * sub-step byte g_MasterSubStep selects the entry. */

MATCH void func_801D2BE8(void) {
    SYS_DISPATCH_BYTE(g_MasterStep3Funcs, g_MasterSubStep);
}
