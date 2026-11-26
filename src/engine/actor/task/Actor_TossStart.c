#include "engine/game/00/game_00.h"

typedef struct GameRouteRequest {
    u8 flags;
    u8 pad_01[3];
    u8 rate;
    u8 pad_05[0x0B];
} GameRouteRequest;

/* func_8019ADE8 */
/* Puts the actor on the position of its source actor, faces it like the leader, starts its route move and launches it. */
MATCH void Actor_TossStart(void) {
    Actor*           work;
    Actor*           work2;
    s32              z;
    GameRouteRequest request;

    TASK(Actor)->direction = g_Game.members[0].facing & 0x7;
    Area_SceneSelectRecord(0x18);
    TASK(Actor)->unk_48       = 0;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->mirror       = 0;
    Script_Select(8);
    work                    = TASK(Actor);
    work->pos.x.fixed       = g_Actors[work->unk_06].pos.x.fixed;
    work->pos.y.fixed       = g_Actors[work->unk_06].pos.y.fixed;
    z                       = g_Actors[work->unk_06].pos.z.fixed;
    work->tint.bytes.flags  = 0;
    work2                   = TASK(Actor);
    work->pos.z.fixed       = z;
    work2->tint.bytes.rgb.b = 0;
    work2->tint.bytes.rgb.g = 0;
    work2->tint.bytes.rgb.r = 0;
    request.rate            = 3;
    request.flags           = 0;
    Area_MoveActorRoute(&request, TASK(Actor)->direction);
    Actor_TossLaunch();
}
