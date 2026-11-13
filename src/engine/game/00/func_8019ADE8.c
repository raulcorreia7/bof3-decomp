#include "game_00.h"

typedef struct GameRouteRequest {
    u8 unk_00;
    u8 pad_01[3];
    u8 unk_04;
    u8 pad_05[0x0B];
} GameRouteRequest;

MATCH void func_8019ADE8(void) {
    Actor*           work;
    Actor*           work2;
    s32              z;
    GameRouteRequest request;

    g_Task->direction_08 = g_Game.members[0].facing & 0x7;
    Area_FindSceneRecord(0x18);
    g_Task->unk_48       = 0;
    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    Actor_SelectScript(8);
    work                     = g_Task;
    work->pos.x.fixed        = g_Actors[work->unk_06].pos.x.fixed;
    work->pos.y.fixed        = g_Actors[work->unk_06].pos.y.fixed;
    z                        = FIELD(s32, &g_Actors[work->unk_06], 0x3Cu);
    work->tint.bytes.flags   = 0;
    work2                    = g_Task;
    work->pos.z.fixed        = z;
    work2->tint.bytes.unk_5F = 0;
    work2->tint.bytes.unk_5E = 0;
    work2->tint.bytes.unk_5D = 0;
    request.unk_04           = 3;
    request.unk_00           = 0;
    Area_MoveActorRoute(&request, g_Task->direction_08);
    func_8019AF1C();
}
