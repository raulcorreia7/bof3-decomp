#include "game_00.h"

/* FAKE: retail reads the row through a non-volatile pointer. */
MATCH void func_801B3488(void) {
    if (D_8014625C & PADLup) {
        func_801C5558();
    } else if (D_8014625C & PADLdown) {
        func_801C5620();
    } else if (D_8014625C & g_InputMasks[INPUT_SLOT_EXAMINE]) {
        func_801C56E4();
    }
    if (!((g_GameFlags | g_AreaWalkFlags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_AdvanceScroll(COORD_INT(((Actor*)SCRATCH_WORK)->pos.z));
        func_801C2710();
    }
}
