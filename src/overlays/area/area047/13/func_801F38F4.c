#include "area047_13.h"

extern s16 D_801492DC;

MATCH void func_801F38F4(void) {
    ((Actor*)g_Task)->pos.x.fixed = TO_COORD(18);
    ORDER_FENCE(); /* FAKE: the order fence keeps the actor store ahead of the target store. */
    g_AreaScrollTargetX           = TO_COORD(18);
    ((Actor*)g_Task)->pos.y.fixed = TO_COORD(36);
    g_AreaScrollTargetY           = TO_COORD(36);
    func_80153DE8();
    COORD_INT(((Actor*)g_Task)->pos.z) = 0x1220;
    Area_AdvanceScroll(0x1220);
    g_AreaCameraAngle.vx = -0x48A;
    D_801492DC           = 0xF8;
}
