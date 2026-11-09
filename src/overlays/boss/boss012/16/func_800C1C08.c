#include "boss012_16.h"
#include "area/spad.h"
#include "overlays/battle/battle.h"

MATCH void func_800C1C08(s32 mode) {
    SPRT*  sprt;
    Actor* task;
    s32    y1;
    s32    y2;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(2, 0, 0x340, 0x100), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));

    sprt = (SPRT*)g_GfxPrimCursor;
    setRGB0(sprt, 0x80, 0x80, 0x80);
    task     = g_Task;
    sprt->x0 = task->unk_18 - 0x28;
    y1       = task->unk_1C;
    y2       = task->gravity - 0x3C;
    sprt->w  = 0x68;
    sprt->u0 = 0;
    sprt->v0 = mode;
    sprt->h  = 0x56;
    sprt->y0 = y1 + y2;
    SetSprt(sprt);
    GFX_AddPrim(1, sizeof(SPRT));
}
