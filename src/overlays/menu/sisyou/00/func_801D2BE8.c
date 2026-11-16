#include "sisyou_00.h"

/* Sub-handler table of sisyou step 3 (g_MasterMenuSteps[3] is func_801D2BE8); the
 * sub-step byte g_MenuMasterSubStep selects the entry. */

MATCH void func_801D2BE8(void) {
    SYS_DISPATCH_BYTE(g_MenuMasterStep3Steps, g_MenuMasterSubStep);
}
