#include "area108_14.h"

MATCH void func_801F384C(void) {
    u16 y;
    u8  timer;

    Area_ProjectPoint(&g_Task->pos.x.fixed, (DVECTOR*)D_1F800034);
    g_Task->screen_x = D_1F800034[0];
    y                = D_1F800034[1];
    g_Task->screen_y = y;
    GFX_DrawShadedDisc((s16)g_Task->screen_x, (s16)y, (s16)g_Task->unk_18, 0xFF, 0xFF);
    ACTOR_COUNT_DOWN(timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        Actor* task;

        task                   = g_Task;
        task->tint.bytes.rgb.b = 0x60;
        task->tint.bytes.rgb.g = 0x60;
        task->tint.bytes.rgb.r = 0x60;
        g_Task->header.mode++;
    }
}
