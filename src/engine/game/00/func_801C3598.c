#include "game_00.h"

MATCH void func_801C3598(void) {
    u8 index;

    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        g_Game.current->u.field.countdown_119--;
        if (g_Game.current->u.field.countdown_119 == 0) {
            index = g_Game.current->character_index;
            g_Characters[index].status &= ~STATUS_CONFUSED;
        }
    }
}
