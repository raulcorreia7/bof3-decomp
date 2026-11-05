#include "area047_13.h"

extern s16 D_801492DC;

MATCH void func_801F38F4(void) {
    ((Actor*)g_Task)->x.fixed = 0x120000;
    ORDER_FENCE(); /* FAKE: the order fence keeps the actor store ahead of the target store. */
    g_AreaScrollTargetX       = 0x120000;
    ((Actor*)g_Task)->y.fixed = 0x240000;
    g_AreaScrollTargetY       = 0x240000;
    func_80153DE8();
    ((Actor*)g_Task)->z.part.integer = 0x1220;
    Area_AdvanceScroll(0x1220);
    g_AreaCameraAngle.vx = -0x48A;
    D_801492DC           = 0xF8;
}
