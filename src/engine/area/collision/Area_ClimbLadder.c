#include "engine/game/00/game_00.h"

/* FAKE: retail reads the row through a non-volatile pointer. */
/* func_801B3488 */
MATCH void Area_ClimbLadder(void) {
    if (g_Game.input & PADLup) {
        func_801C5558();
    } else if (g_Game.input & PADLdown) {
        func_801C5620();
    } else if (g_Game.input & g_InputMasks[FIELD_INPUT_INTERACT]) {
        func_801C56E4();
    }
    if (!((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_ScrollAdvance(COORD_INT((g_Task)->pos.z));
        Area_ScrollUpdateWalk();
    }
}
