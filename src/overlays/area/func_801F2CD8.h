#include "sys/gameui.h"

/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F2CD8;
 * every change here must verify every member address. */
MATCH void func_801F2CD8(void) {
    if (D_801490C7 == 1) {
        g_MessageRequest            = 0x5F;
        g_SaveData.scene_event.step = 1;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
