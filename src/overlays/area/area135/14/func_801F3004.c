#include "area135_14.h"

MATCH void func_801F3004(s32 x, s32 y, s32 width, s32 height) {
    s16*   rect;
    s16*   next;
    Actor* work;

    rect            = (s16*)g_GfxPrimCursor;
    rect[0]         = x;
    rect[1]         = y;
    next            = rect + 4;
    g_GfxPrimCursor = (u8*)next;
    rect[2]         = width;
    rect[3]         = height;
    SetTexWindow((DR_TWIN*)next, (RECT*)rect);
    work = g_Task;
    Area_AddCellPrim(work->x.fixed, work->y.fixed, 0, 0xC);
}
