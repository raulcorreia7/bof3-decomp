#include "area077_14.h"

MATCH void func_801F3F08(void) {
    u8         scratch[0x20];
    WorldSpin* spin;
    Actor*     work;
    s32        frame;
    u8         index;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 0x380, 0x100), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    PushMatrix();
    Area_SetCameraMatrix(scratch);
    spin  = (WorldSpin*)(AREA_WORK + 0xD04);
    index = 0;
    do {
        Area_DrawSpinTriangle(spin);
        work = g_Task;
        spin->spin_angle += 0x10;
        if (work->timer < 4) {
            spin->fade += 0x20;
        } else {
            spin->fade -= 2;
        }
        spin++;
        index += 1;
    } while (index < 0x20);

    PopMatrix();
    work     = g_Task;
    frame    = work->vx + 1;
    work->vx = frame;
    if (frame >= 0xB9) {
        func_80196070();
    }
}
