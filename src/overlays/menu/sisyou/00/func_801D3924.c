#include "sisyou_00.h"

/* Sub-handler table of sisyou step 5 (g_MasterMenuStates[5] is func_801D3924); the
 * sub-step byte g_MenuMasterSubStep selects the entry. */

MATCH void func_801D3924(void) {
    SYS_DISPATCH_BYTE(g_MenuMasterStep5Funcs, g_MenuMasterSubStep);
}
