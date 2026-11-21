#include "game_00.h"

/* func_801C3598 */
/* Counts down the confusion of the active character and clears it at zero. */
MATCH void Party_TickConfusion(void) {
    u8 index;

    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        g_Game.current->u.field.countdown--;
        if (g_Game.current->u.field.countdown == 0) {
            index = g_Game.current->character_index;
            g_Characters[index].status &= ~STATUS_CONFUSED;
        }
    }
}
