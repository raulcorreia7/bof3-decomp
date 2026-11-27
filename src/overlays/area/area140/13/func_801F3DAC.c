#include "area140_13.h"

MATCH void func_801F3DAC(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
    if (g_Game.members[0].chr.character_id == CHAR_ID_MOMO || g_Game.members[0].chr.character_id == CHAR_ID_PECO || g_Game.members[0].chr.character_id == CHAR_ID_RYU_ADULT) {
        SYS_SetFlag(g_SceneEventFlags, 84);
        Area_CellSetPalette(2, 7);
        SELF(Actor)->header.flags = 0;
    }
}
