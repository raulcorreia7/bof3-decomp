#include "game_00.h"

MATCH void func_801C3204(void) {
    u8 index;

    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_POISONED) {
        g_Game.current->u.field.flags_118 = 0x0A;
    }
    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        g_Game.current->u.field.countdown_119 = 0x28;
    }
}
