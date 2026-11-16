#include "sisyou_00.h"

/* Sub-handler table of sisyou step 1 (g_MasterMenuSteps[1] is func_801D2688); the
 * sub-step byte g_MenuMasterSubStep selects the entry. */

MATCH void func_801D2688(void) {
    SYS_DISPATCH_BYTE(g_MasterMenuSubSteps, g_MenuMasterSubStep);
}
