#include "game_00.h"

MATCH void Actor_Clear(void) {
    g_SpadWork->flags_00 = 0;
    g_SpadWork->unk_01   = 0;
    ACTOR_CLEAR_STATE();
    g_SpadWork->unk_03 = 0;
    g_SpadWork->unk_04 = 0;
}
