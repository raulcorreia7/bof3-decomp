#include "area175_13.h"

/* func_801F2CD8 */
MATCH void Area_UpdateSpin(void) {
    u8         scratch[0x20];
    WorldSpin* spin;
    u8         index;
    u8         timer;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    Area_SetCameraMatrix(scratch);

    spin  = (WorldSpin*)AREA_WORK;
    index = 0;
    do {
        Area_DrawSpinTriangle(spin);
        spin->spin_angle += 0x10;
        if (g_Task->timer < 4) {
            spin->fade += 0x20;
        } else {
            spin->fade -= 2;
        }
        spin++;
        index += 1;
    } while (index < 0x20);

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer >= 0x45) {
        g_Task->header.mode += 1;
    }
}
