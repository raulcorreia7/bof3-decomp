#define FAKE_DECL_TASK_VOLATILE
#include "engine/slus/slus.h"
#include <inline_c.h>

/* Projects the area position through the GTE and registers visible actors. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015A9A4(void) {
    SVECTOR vec;
    s16     sxy[2];
    Actor*  task;
    Actor*  actor;
    s32     dx;
    s32     dy;
    s32     sum;
    u16     key;
    s32     x;
    s32     y;
    s32     pad;
    u8      count;
    u16     sy;
    u8      step;
    s8      sstep;

    task = TASK(Actor);
    dx   = COORD_INT(task->pos.x) - g_AreaTileOriginX;
    dy   = COORD_INT(task->pos.y) - g_AreaTileOriginY;
    if (COORD_FRAC(task->pos.x) != 0) {
        dy += 1;
    }
    sum = dx + dy;
    key = sum + 1;
    if (COORD_FRAC(TASK(Actor)->pos.y) == 0) {
        key = sum;
    }
    actor         = TASK(Actor);
    task->unk_32  = key;
    key           = (actor->unk_32 + (s8)((u8*)actor->range_54.table)[1]) << 8;
    actor->unk_32 = key;
    if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
        if (D_8014933F != 0) {
            actor->unk_32 = key | ((actor->pos.x.fixed >> 15) & BYTE_MASK);
        } else {
            actor->unk_32 = key | ((actor->pos.y.fixed >> 15) & BYTE_MASK);
        }
    } else {
        actor->unk_32 = key | ((((u16)COORD_INT(actor->pos.z) >> 5) & BYTE_MASK) ^ 0x80);
    }
    if (!(((u8*)TASK(Actor)->range_54.table)[3] & 0x10)) {
        Actor_ReadValue();
    }
    actor = TASK(Actor);
    setVector(&vec, (actor->pos.x.fixed >> 9) - 0x4000, (actor->pos.y.fixed >> 9) - 0x4000, -COORD_INT(actor->pos.z) / 2);
    gte_ldv0(&vec);
    gte_rtps();
    gte_stsxy(sxy);
    gte_stszotz(&TASK(Actor)->unk_60);
    actor           = TASK(Actor);
    actor->screen_x = sxy[0];
    sy              = sxy[1];
    actor->screen_y = sy;
    pad             = (((u8*)actor->range_54.table)[3] >> 1) & 4;
    x               = (s16)actor->screen_x;
    if ((((&D_80182174)[pad] + 320) < x) || (x < -(s32)(&D_80182175)[pad]) || (((&D_80182176)[pad] + 240) < (s16)sy) || ((s16)sy < -(s32)(&D_80182177)[pad])) {
        TASK(Actor)->header.flags |= 0x80;
        return;
    }
    actor->header.flags &= 0x7F;
    count = g_AreaGridActorCount;
    if (count < 40) {
        g_AreaGridActorCount    = count + 1;
        g_AreaGridActors[count] = (s32)g_Task;
    }
}
#else
INCLUDE_ASM(func_8015A9A4);
#endif
