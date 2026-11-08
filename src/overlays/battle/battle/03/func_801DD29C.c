#include "battle_03.h"

MATCH void func_801DD29C(void) {
    s8* p;
    s8* r;
    u8  v;

    p = &g_BattleCommandCount;
    if (*p < 3) {
        r = p;
        while (*r < 3) {
            v = D_801462F6[*r];
            if ((v & BYTE_MASK) == GAME_NONE) {
                break;
            }
            ((u8*)r)[-0x15]                                       = v;
            g_Game.members[(v & BYTE_MASK)].u.turn.command.type   = BATTLE_COMMAND_ATTACK;
            g_Game.members[((u8*)r)[-0x15]].u.turn.command.target = 3;
            ((u8*)r)[0] += 1;
        }
    }
}
