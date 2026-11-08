#include "area108_14.h"

MATCH void func_801F3920(void) {
    Actor* task;
    u16    y;

    Area_ProjectPoint(&g_Task->pos.x.fixed, (DVECTOR*)D_1F800034);
    g_Task->screen_x = D_1F800034[0];
    y                = D_1F800034[1];
    g_Task->screen_y = y;
    GFX_DrawShadedDisc((s16)g_Task->screen_x, (s16)y, (s16)g_Task->unk_18, 0xFF, g_Task->tint.bytes.flags);
    func_801F3BA0();
    func_801F3C84();
    task = g_Task;
    task->tint.bytes.flags -= 2;
    task->unk_18 -= 0xA;
    if (g_Task->unk_18 <= 0) {
        g_ScriptVars[0]++;
        g_Task->header.mode++;
    }
}
