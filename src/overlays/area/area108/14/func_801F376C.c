#include "area108_14.h"

MATCH void func_801F376C(void) {
    Actor* task;
    u16*   screen;
    u16    screen_y;

    screen = (u16*)D_1F800034;
    Area_ProjectPoint((s32*)&g_Task->pos, (DVECTOR*)screen);
    g_Task->screen_x = screen[0];
    screen_y         = screen[1];
    g_Task->screen_y = screen_y;
    GFX_DrawShadedDisc(g_Task->screen_x, (s16)screen_y, g_Task->unk_18, 0xFF, g_Task->tint.bytes.flags);
    task = g_Task;
    task->tint.bytes.flags += 2;
    task->unk_18 += 5;
    if (g_Task->unk_18 >= 0x191) {
        g_Task->timer = 0xF;
        g_Task->header.mode += 1;
    }
}
