#include "area056_13.h"

MATCH void func_801F3354(void) {
    s16 height;
    s16 landing_height;

    SELF(Actor)->vz += SELF(Actor)->gravity;
    Actor_MovementUpdate();
    height         = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    landing_height = height;
    FAKE_OPAQUE(height); /* FAKE: keeps the compare's sign extension on the call result in v0. */
    if (COORD_INT(SELF(Actor)->pos.z) < height) {
        COORD_INT(SELF(Actor)->pos.z) = landing_height;
        SELF(Actor)->vz               = 0;
        SELF(Actor)->gravity          = 0;
        SELF(Actor)->unk_04           = 2;
    }
    if ((SELF(Actor)->unk_05 == 0) && (((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0)) {
        Area_ScrollAdvance(COORD_INT(SELF(Actor)->pos.z));
    }
    g_Game.current->u.field.unk_122 -= 2;
}
