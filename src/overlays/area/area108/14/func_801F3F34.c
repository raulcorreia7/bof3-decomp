#include "area108_14.h"

MATCH void func_801F3F34(void) {
    Actor* actor;

    SELF(Actor)->timer++;
    actor = SELF(Actor);
    if (actor->timer == 1) {
        Area_CellSetPalette((s16)(COORD_INT(actor->pos.x) + 1), COORD_INT(actor->pos.y));
    }
    actor = SELF(Actor);
    if (actor->timer == 5) {
        Area_CellSetPalette(COORD_INT(actor->pos.x), COORD_INT(actor->pos.y));
    }
    if (SELF(Actor)->timer == 15) {
        SYS_ClearFlag(g_SceneEventFlags, 28);
        Actor_Clear();
    }
}
