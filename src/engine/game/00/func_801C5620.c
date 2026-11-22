#include "game_00.h"

MATCH void func_801C5620(void) {
    u16 count;
    s32 x;
    s32 y;
    s16 result;

    x                             = TASK(Actor)->pos.x.fixed;
    count                         = COORD_INT(TASK(Actor)->pos.z);
    y                             = TASK(Actor)->pos.y.fixed;
    COORD_INT(TASK(Actor)->pos.z) = count - 16;
    result                        = Area_HeightRead(x, y);

    if ((s16)COORD_INT(TASK(Actor)->pos.z) < result) {
        COORD_INT(TASK(Actor)->pos.z) = (u16)result;
        Script_Select(TASK(Actor)->direction);
        GFX_PaletteLoad(GAME_PALETTE_STAGE + TASK(Actor)->unk_05 * 0x40u, 0);
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
    }

    Script_AnimStepLoop();
}
