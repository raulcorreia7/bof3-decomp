#define FAKE_DECL_TASK_VOLATILE
#include "engine/slus/slus.h"
#include <inline_c.h>

/* projects the record's position through the GTE into screen halfwords at +0x2E/+0x30 and a depth word at +0x60;
 * clears or sets the record's off-screen flag (bit 7 of the first byte) and registers on-screen records in D_8014828C.
 */
/* Reordered coordinate assignments leave the origin load difference at +0x0C; volatile reads and a barrier alter the prologue. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015A9A4(void) {
    SVECTOR vec;
    s16     sxy[2];
    Actor*  task;
    Actor*  actor;
    s32     dx;
    s32     dy;
    s32     sum;
    s32     key;
    s32     low;
    s32     x;
    s32     y;
    s32     pad;
    u8      count;
    u16     sy;
    u8      step;
    s8      sstep;

    task = g_Task;
    dx   = COORD_INT(task->pos.x) - g_AreaTileOriginX;
    dy   = COORD_INT(task->pos.y) - g_AreaTileOriginY;
    if (COORD_FRAC(task->pos.x) != 0) {
        dy += 1;
    }
    sum = dx + dy;
    key = sum + 1;
    if (COORD_FRAC(g_Task->pos.y) == 0) {
        key = sum;
    }
    actor         = g_Task;
    task->unk_32  = key;
    key           = (actor->unk_32 + ((((u8*)actor->range_54.table)[1] << 24) >> 24)) << 8;
    actor->unk_32 = key;
    if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
        if (D_8014933F != 0) {
            low = actor->pos.x.fixed >> 15;
        } else {
            low = actor->pos.y.fixed >> 15;
        }
        low &= BYTE_MASK;
    } else {
        low = (((u16)COORD_INT(actor->pos.z) >> 5) & BYTE_MASK) ^ 0x80;
    }
    actor->unk_32 = key | low;
    if (!(((u8*)g_Task->range_54.table)[3] & 0x10)) {
        Actor_ReadValue();
    }
    actor  = g_Task;
    vec.vx = (actor->pos.x.fixed >> 9) - 0x4000;
    vec.vy = (actor->pos.y.fixed >> 9) - 0x4000;
    vec.vz = -COORD_INT(actor->pos.z) / 2;
    gte_ldv0(&vec);
    gte_rtps();
    gte_stsxy(sxy);
    gte_stszotz(&g_Task->unk_60);
    actor           = g_Task;
    actor->screen_x = sxy[0];
    sy              = sxy[1];
    actor->screen_y = sy;
    pad             = (((u8*)actor->range_54.table)[3] >> 1) & 4;
    x               = (s16)actor->screen_x;
    if ((((&D_80182174)[pad] + 320) < x) || (x < -(s32)(&D_80182175)[pad]) || (((&D_80182176)[pad] + 240) < (s16)sy) || ((s16)sy < -(s32)(&D_80182177)[pad])) {
        g_Task->header.flags |= 0x80;
        return;
    }
    actor->header.flags &= 0x7F;
    count = D_8014832D;
    if (count < 40) {
        D_8014832D        = count + 1;
        D_8014828C[count] = (s32)g_Task;
    }
}
#else
INCLUDE_ASM(func_8015A9A4);
#endif
