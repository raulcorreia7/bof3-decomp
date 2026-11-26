#include "engine/game/00/game_00.h"

/* func_801C5620 */
/* Lowers the actor 16 units; at the ground height it returns the member to the walk mode. */
MATCH void Area_ClimbDown(void) {
    u16 z;
    s32 pos_x;
    s32 pos_y;
    s16 ground;

    pos_x                         = SELF(Actor)->pos.x.fixed;
    z                             = COORD_INT(SELF(Actor)->pos.z);
    pos_y                         = SELF(Actor)->pos.y.fixed;
    COORD_INT(SELF(Actor)->pos.z) = z - 16;
    ground                        = Area_HeightRead(pos_x, pos_y);

    if ((s16)COORD_INT(SELF(Actor)->pos.z) < ground) {
        COORD_INT(SELF(Actor)->pos.z) = (u16)ground;
        Script_Select(SELF(Actor)->direction);
        GFX_PaletteLoad(GAME_PALETTE_STAGE + SELF(Actor)->unk_05 * 0x40u, 0);
        g_Game.current->u.field.mode.unsigned_value = 0;
        SELF(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
    }

    Script_AnimStepLoop();
}
