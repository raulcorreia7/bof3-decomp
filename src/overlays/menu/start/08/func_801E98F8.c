#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte, the two
 * byte lookup tables and the draw helper owned by this overlay. */

MATCH void func_801E98F8(void) {
    D_801ED3FC[g_MenuPanelTaskCurrent->state]();
    func_801DBF04((s16)g_MenuPanelTaskCurrent->x, (s16)g_MenuPanelTaskCurrent->y,
                  g_CharSlot[D_80144F5A[((u8*)g_MenuPanelTaskCurrent)[0xA]]]);
}
