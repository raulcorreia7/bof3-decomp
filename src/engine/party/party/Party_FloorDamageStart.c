#include "engine/game/00/game_00.h"

/* func_801B9210 */
/* Applies the floor damage, knocks the actor back a step and starts the blink. */
MATCH void Party_FloorDamageStart(void) {
    u8  saved;
    u8  mode;
    s32 v;

    if (SELF(Actor)->tint.bytes.flags != 0) {
        GFX_PaletteLoad((GAME_PALETTE_STAGE + (SELF(Actor)->unk_05 << 6)), 0);
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(Actor)->tint.bytes.flags = 0;
        ACTOR_CLEAR_TINT();
    }
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    if ((SELF(Actor)->pos.x.fixed & 0x7FFF) != 0 || (SELF(Actor)->pos.y.fixed & 0x7FFF) != 0) {
        SELF(Actor)->pos.x.fixed      = (SELF(Actor)->pos.x.fixed + 0x4800) & ~0x7FFF;
        SELF(Actor)->pos.y.fixed      = (SELF(Actor)->pos.y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(SELF(Actor)->pos.z) = Area_HeightReadStep(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->direction);
        if (SELF(Actor)->unk_05 == 0) {
            v                           = SELF(Actor)->pos.x.fixed;
            g_AreaCamera.scroll_x.fixed = v;
            v                           = SELF(Actor)->pos.y.fixed;
            g_AreaCamera.scroll_y.fixed = v;
            Area_InitMapRenderer();
        }
    }
    saved                  = SELF(Actor)->direction;
    SELF(Actor)->direction = saved ^ 0x4;
    mode                   = func_801B9598();
    if (mode == 1 || mode == 3) {
        if ((Area_GetActorFacingStepX() << 24) != 0) {
            SELF(Actor)->timer = 0;
            Actor_ClearVelocity();
        } else {
            Area_RunWalk();
            SELF(Actor)->timer--;
            Actor_Move();
        }
    } else {
        Actor_ClearVelocity();
    }
    Party_FloorDamageApply(SELF(Actor)->param.unk_0B);
    SELF(Actor)->direction = saved;
    SELF(Actor)->unk_0A    = 8;
    Script_Request(SELF(Actor)->direction);
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 8));
    SELF(Actor)->unk_03++;
}
