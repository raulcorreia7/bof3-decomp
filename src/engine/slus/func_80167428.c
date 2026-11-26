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

    if (g_PadStates[0].pressed & PADstart) {
        player            = g_Game.current;
        g_AreaCameraSpeed = 0x20;
        px                = &g_AreaScrollTargetX;
        py                = &g_AreaScrollTargetY;
        dx                = abs(*px - player->pos.x.fixed);
        dy                = abs(*py - player->pos.y.fixed);
        *px               = player->pos.x.fixed;
        *py               = player->pos.y.fixed;
        if (dx < dy) {
            dx = dy;
        }
        steps = dx >> 13;
        if (steps != 0) {
            g_AreaCameraHeightDelta = (s16)(player->pos.z.part.integer - g_AreaCameraHeight) / steps;
        } else {
            g_AreaCameraHeightDelta = 0;
        }
        g_Game.current->u.field.counter.unsigned_value = 3;
        TASK(Actor)->header.flags |= 0x40;
        TASK(Actor)->header.mode = 3;
        return;
    }
    if (D_8014625C & g_InputMasks[FIELD_INPUT_VIEW]) {
        g_Game.current->u.field.counter.unsigned_value = 3;
        substate                                       = &g_GameEntrySubstate;
        (*substate)++;
        TASK(Actor)->header.mode = 1;
        TASK(Actor)->header.step = 0;
        return;
    }
    if (!(Game_GetInput() & BYTE_MASK)) {
        g_Game.current->u.field.counter.unsigned_value = 3;
        work                                           = TASK(Actor);
        work->timer                                    = 0;
        work->vx                                       = 0;
        work->vy                                       = 0;
        work->vz                                       = 0;
        g_AreaCameraSpeed                              = 0;
        g_AreaCameraHeightDelta                        = 0;
        TASK(Actor)->header.mode                       = 1;
        return;
    }
    if (!func_801B0E44()) {
        work = TASK(Actor);
        dx   = abs(g_Game.members[0].pos.x.fixed - (work->pos.x.fixed + g_FacingSteps[work->direction].x));
        dy   = abs(g_Game.members[0].pos.y.fixed - (work->pos.y.fixed + g_FacingSteps[work->direction].y));
        if (dx > TO_COORD(6) || dy > TO_COORD(6) || g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            work                     = TASK(Actor);
            work->timer              = 0;
            work->vx                 = 0;
            work->vy                 = 0;
            work->vz                 = 0;
            g_AreaCameraSpeed        = 0;
            g_AreaCameraHeightDelta  = 0;
            TASK(Actor)->header.mode = 1;
        } else {
            if ((D_8014625C & g_InputMasks[FIELD_INPUT_RUN]) ? g_AutoRun ^ 1 : g_AutoRun) {
                g_Game.current->u.field.counter.unsigned_value = 4;
            } else {
                g_Game.current->u.field.counter.unsigned_value = 3;
            }
            Area_RunWalk();
            func_801C4C48();
            TASK(Actor)->timer--;
            Actor_MovementUpdate();
            TASK(Actor)->header.mode = 2;
        }
    } else {
        g_Game.current->u.field.counter.unsigned_value = 3;
        TASK(Actor)->timer                             = 0;
        TASK(Actor)->header.mode                       = 1;
    }
    g_GameStateIndex = GAME_REQUEST_SCENE_CAMERA;
    g_AreaWalkFlags &= 0x1F;
}
#else
INCLUDE_ASM(func_80167428);
#endif
