#include "engine/slus/slus.h"

#ifdef NON_MATCHING
NON_MATCHING void func_80167428(void) {
    PartyMember* player;
    Actor*       work;
    s32          dx;
    s32          dy;
    s32*         px;
    s32*         py;
    u16*         substate;
    u8           steps;
    s32          x;
    s16          rise;

    if (g_PadStates[0].pressed & PADstart) {
        px                = &g_AreaScrollTargetX;
        g_AreaCameraSpeed = 0x20;
        player            = g_Game.current;
        py                = &g_AreaScrollTargetY;
        x                 = player->pos.x.fixed;
        dx                = abs(*px - x);
        dy                = abs(*py - player->pos.y.fixed);
        *px               = x;
        *py               = player->pos.y.fixed;
        if (dx < dy) {
            dx = dy;
        }
        steps = dx >> 13;
        rise  = player->pos.z.part.integer - g_AreaCameraHeight;
        if (steps != 0) {
            g_AreaCameraHeightDelta = rise / steps;
        } else {
            g_AreaCameraHeightDelta = 0;
        }
        g_Game.current->u.field.counter.unsigned_value = 3;
        SELF(Actor)->header.flags |= 0x40;
        SELF(Actor)->header.mode = 3;
        return;
    }
    if (D_8014625C & g_InputMasks[FIELD_INPUT_VIEW]) {
        g_Game.current->u.field.counter.unsigned_value = 3;
        substate                                       = &g_GameEntrySubstate;
        (*substate)++;
        SELF(Actor)->header.mode = 1;
        SELF(Actor)->header.step = 0;
        return;
    }
    if (!(Game_GetInput() & BYTE_MASK)) {
        g_Game.current->u.field.counter.unsigned_value = 3;
        work                                           = SELF(Actor);
        work->timer                                    = 0;
        work->vx                                       = 0;
        work->vy                                       = 0;
        work->vz                                       = 0;
        g_AreaCameraSpeed                              = 0;
        g_AreaCameraHeightDelta                        = 0;
        SELF(Actor)->header.mode                       = 1;
        return;
    }
    if (!func_801B0E44()) {
        work = SELF(Actor);
        dx   = abs(g_Game.members[0].pos.x.fixed - (work->pos.x.fixed + g_FacingSteps[work->direction].x));
        dy   = abs(g_Game.members[0].pos.y.fixed - (work->pos.y.fixed + g_FacingSteps[work->direction].y));
        if (dx > TO_COORD(6) || dy > TO_COORD(6) || g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            work                     = SELF(Actor);
            work->timer              = 0;
            work->vx                 = 0;
            work->vy                 = 0;
            work->vz                 = 0;
            g_AreaCameraSpeed        = 0;
            g_AreaCameraHeightDelta  = 0;
            SELF(Actor)->header.mode = 1;
        } else {
            if ((D_8014625C & g_InputMasks[FIELD_INPUT_RUN]) ? g_AutoRun ^ 1 : g_AutoRun) {
                g_Game.current->u.field.counter.unsigned_value = 4;
            } else {
                g_Game.current->u.field.counter.unsigned_value = 3;
            }
            Area_RunWalk();
            func_801C4C48();
            SELF(Actor)->timer--;
            Actor_MovementUpdate();
            SELF(Actor)->header.mode = 2;
        }
    } else {
        g_Game.current->u.field.counter.unsigned_value = 3;
        SELF(Actor)->timer                             = 0;
        SELF(Actor)->header.mode                       = 1;
    }
    g_GameStateIndex = GAME_REQUEST_SCENE_CAMERA;
    g_AreaWalkFlags &= 0x1F;
}
#else
INCLUDE_ASM(func_80167428);
#endif
