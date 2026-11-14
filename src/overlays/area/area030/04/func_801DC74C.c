#include "area030_04.h"

/* Initializes the AREA030 field when the gate halfword is clear:
 * sets the two world scale words, resets the object records, arms the field
 * effect, and starts the matching field cue. */
MATCH void func_801DC74C(void) {
    if (WINDOW_EFFECT_IDLE()) {
        SYS_ThreadWait(1);
        g_AreaScrollTargetX = TO_COORD(15);
        g_AreaScrollTargetY = TO_COORD(60);
        func_80153DE8();
        func_801E0A30();
        UI_SetMode(3);
        if (g_Game.current->chr.character_id == CHAR_ID_RYU_YOUNG) {
            Actor_BeginScript(0xA, 2);
        } else {
            Actor_SelectScript(0xB);
        }
        FISHING_STATE->sub_index_03 = 1;
    }
}
