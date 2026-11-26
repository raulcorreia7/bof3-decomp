#include "engine/game/00/game_00.h"

/* func_801B9210 */
/* Applies the floor damage, knocks the actor back a step and starts the blink. */
MATCH void Party_FloorDamageStart(void) {
    u8  saved;
    u8  mode;
    s32 v;

    if (TASK(Actor)->tint.bytes.flags != 0) {
        GFX_PaletteLoad((GAME_PALETTE_STAGE + (TASK(Actor)->unk_05 << 6)), 0);
        TASK(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        TASK(Actor)->tint.bytes.flags = 0;
        ACTOR_CLEAR_TINT();
    }
    TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    if ((TASK(Actor)->pos.x.fixed & 0x7FFF) != 0 || (TASK(Actor)->pos.y.fixed & 0x7FFF) != 0) {
        TASK(Actor)->pos.x.fixed      = (TASK(Actor)->pos.x.fixed + 0x4800) & ~0x7FFF;
        TASK(Actor)->pos.y.fixed      = (TASK(Actor)->pos.y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightReadStep(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->direction);
        if (TASK(Actor)->unk_05 == 0) {
            v                           = TASK(Actor)->pos.x.fixed;
            g_AreaCamera.scroll_x.fixed = v;
            v                           = TASK(Actor)->pos.y.fixed;
            g_AreaCamera.scroll_y.fixed = v;
            Area_InitMapRenderer();
        }
    }
    saved                  = TASK(Actor)->direction;
    TASK(Actor)->direction = saved ^ 0x4;
    mode                   = func_801B9598();
    if (mode == 1 || mode == 3) {
        if ((Area_GetActorFacingStepX() << 24) != 0) {
            TASK(Actor)->timer = 0;
            Actor_ClearVelocity();
        } else {
            Area_RunWalk();
            TASK(Actor)->timer--;
            Actor_Move();
        }
    } else {
        Actor_ClearVelocity();
    }
    Party_FloorDamageApply(TASK(Actor)->param.unk_0B);
    TASK(Actor)->direction = saved;
    TASK(Actor)->unk_0A    = 8;
    Script_Request(TASK(Actor)->direction);
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 8));
    TASK(Actor)->unk_03++;
}
