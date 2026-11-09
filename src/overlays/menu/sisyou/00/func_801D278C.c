#include "sisyou_00.h"

/* Sub-handler table of sisyou step 2 (g_MasterMenuStates[2] is func_801D278C); the
 * sub-step byte g_MenuMasterSubStep selects the entry. */

MATCH void func_801D278C(void) {
    SYS_DISPATCH_BYTE(g_MenuMasterStep2Funcs, g_MenuMasterSubStep);
}
