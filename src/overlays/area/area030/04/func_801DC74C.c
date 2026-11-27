#include "area030_04.h"

/* Initializes the AREA030 field when the gate halfword is clear:
 * sets the two world scale words, resets the object records, arms the field
 * effect, and starts the matching field cue. */
MATCH void func_801DC74C(void) {
    if (WINDOW_EFFECT_IDLE()) {
        SYS_ThreadWait(1);
        g_AreaCamera.scroll_x.fixed = TO_COORD(15);
        g_AreaCamera.scroll_y.fixed = TO_COORD(60);
        Area_InitMapRenderer();
        func_801E0A30();
        UI_ModeSet(3);
        if (g_Game.current->chr.character_id == CHAR_ID_RYU_YOUNG) {
            Script_Begin(0xA, 2);
        } else {
            Script_Select(0xB);
        }
        SELF(FishingState)->sub_index = 1;
    }
}
