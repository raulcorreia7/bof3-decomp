#include "game_00.h"

MATCH void func_801AD3B4(void) {
    u32 choice;

    choice = RANDOM_MASK(0xF);
    if ((g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4(((g_Game.members[0].facing ^ 0x4) & 0x7));
    }
    func_801ADAC0(choice >= 7 ? 2 : 3);
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    g_Task->unk_04 = 1;
}
