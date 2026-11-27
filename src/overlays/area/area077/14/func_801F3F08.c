#include "area077_14.h"

MATCH void func_801F3F08(void) {
    u8          scratch[0x20];
    SpinEffect* spin;
    Actor*      work;
    s32         frame;
    u8          index;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    PushMatrix();
    Camera_SetMatrix(scratch);
    spin  = (SpinEffect*)(AREA_WORK + 0xD04);
    index = 0;
    do {
        Area_DrawSpinTriangle(spin);
        work = SELF(Actor);
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
    work     = SELF(Actor);
    frame    = work->vx + 1;
    work->vx = frame;
    if (frame >= 0xB9) {
        func_80196070();
    }
}
