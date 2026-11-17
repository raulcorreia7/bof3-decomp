#include "game_00.h"

MATCH void func_801B7024(void) {
    u8 flags;

    if ((u8)func_801C29A0(4) == 0)
        return;
    flags                         = g_Game.current->u.field.flags;
    g_Game.current->u.field.flags = (flags & 0xFD);
    g_Task->unk_03                = 1;
}
