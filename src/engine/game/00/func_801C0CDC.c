#include "game_00.h"

MATCH void func_801C0CDC(void) {
    u8  state;
    s32 mode;

    state = g_Game.members[D_80146262].facing;
    if (state == 5 || state == 3) {
        mode = 2;
    } else {
        mode = 3;
    }
    func_801C0F9C(mode);
}
