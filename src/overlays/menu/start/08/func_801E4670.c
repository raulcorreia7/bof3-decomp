#include "start_08.h"

/* Start-overlay state byte and the prompt/effect hooks this state runs. */

MATCH void func_801E4670(void) {
    Party_InitDefaults();
    D_801ED7D8      = s_CampMenuState;
    g_AreaDrawFlags = AREA_DRAW_SORTED_RECORDS;
    D_801ED7DC      = 0;
    D_801ED7E4      = 0;
    D_801ED7E0      = 0;
    D_801ED7E8      = 2;
    func_801E7000();
    UI_SetMode(1);
    g_MenuStartStep += 1;
}
