#include "engine/game/00/game_00.h"

/* func_801B707C */
/* Fades the actor back in and restores its palette. */
MATCH void Party_ScriptWalkFadeIn(void) {
    if (func_801C27E0(4) & BYTE_MASK) {
        g_Game.current->u.field.flags &= 0xFB;
        SELF(Actor)->unk_03 = 1;
    }
}
