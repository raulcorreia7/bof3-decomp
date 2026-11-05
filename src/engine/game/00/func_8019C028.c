#include "game_00.h"

MATCH s32 func_8019C028(void) {
    s8 slot;
    s8 other;

    slot = func_801BDE14(g_Task->x.fixed, g_Task->y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].flags_74 |= ACTOR_FLAG_INTERACTION_PENDING;
    } else {
        other = func_801BE0C0(g_Task->x.fixed, g_Task->y.fixed, 0);
        if (other == slot) {
            goto fail; /* the other slot is the same slot */
        }
        if (other != 0) {
            D_80145E92[other * BATTLE_PARTY_STRIDE] = 1;
        }
    }
    g_Task->mode = 4;
    func_8014D978();
    Area_SetDrawMode();
    return 1;
fail:
    return 0;
}
