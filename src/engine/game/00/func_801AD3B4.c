#include "game_00.h"

MATCH void func_801AD3B4(void) {
    u32 choice;

    choice = RANDOM_MASK(0xF);
    if ((g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4((u8)((D_80145E98 ^ 4) & 7));
    }
    func_801ADAC0(choice >= 7 ? 2 : 3);
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    g_SpadWork->unk_04 = 1;
}
