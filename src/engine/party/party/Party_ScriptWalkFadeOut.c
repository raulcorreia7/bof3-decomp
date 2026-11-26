#include "engine/game/00/game_00.h"

/* func_801B7024 */
/* Fades the actor out until its tint reaches the end value. */
MATCH void Party_ScriptWalkFadeOut(void) {
    u8 flags;

    if ((u8)func_801C29A0(4) == 0)
        return;
    flags                         = g_Game.current->u.field.flags;
    g_Game.current->u.field.flags = (flags & 0xFD);
    SELF(Actor)->unk_03           = 1;
}
