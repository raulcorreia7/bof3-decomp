#include "game_00.h"

/* The retail leaves the work pointer in $a1 at this call. The callee overwrites
 * $a1 with its own zero operand, so the value is caller context and not part
 * of the shared prototype; the cast keeps the $a1 write. */

/* FAKE: retail reads the screen origin as unsigned halfwords (lhu). */
MATCH void func_8019A3FC(void) {
    Actor* work;
    Actor* other;
    Actor* ptr;
    s32    delta;
    s32    total;

    Area_SceneSelectRecord(0x18);

    ptr         = g_Task;
    ptr->unk_48 = 0;

    work               = g_Task;
    delta              = work->vx;
    total              = *(u16*)&work->screen_x + delta;
    delta              = work->vy;
    work->active_flags = 0;
    work->screen_x     = total;
    total              = *(u16*)&work->screen_y;
    other              = g_Task;
    work->screen_y     = (total - delta);
    other->mirror      = 0;

    work             = g_Task;
    work->draw_layer = 2;

    if (g_Task->unk_06 == 3) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        work                     = g_Task;
        work->tint.bytes.flags   = 1;
        work                     = g_Task;
        work->tint.steps.delta.b = -8;
        work->tint.steps.delta.g = -8;
        work->tint.steps.delta.r = -8;
        work                     = g_Task;
        work->timer              = 20;
    } else {
        g_Task->tint.bytes.flags = 0;
        ptr                      = g_Task;
        ptr->tint.bytes.rgb.b    = 0;
        ptr->tint.bytes.rgb.g    = 0;
        ptr->tint.bytes.rgb.r    = 0;
        work                     = g_Task;
        work->timer              = 16;
    }

    ((void (*)(u8, Actor*))Script_Select)(s_SceneHandlerIds[g_Task->unk_06], other);

    g_Task->header.mode = 1;
}
