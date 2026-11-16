#include "game_00.h"

MATCH void func_801C3598(void) {
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
