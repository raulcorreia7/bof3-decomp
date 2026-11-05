#include "start_08.h"

MATCH void func_801EA50C(void) {
    D_801ED58C[g_MenuCurrentPanel->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_801DE5D4(((u8*)g_CharSlot)[D_80144F5A[g_MenuCurrentPanel->unk_0C]], g_MenuCurrentPanel->x,
                  g_MenuCurrentPanel->y, ((s32*)g_MenuCurrentPanel)[8], g_MenuCurrentPanel->flags, g_MenuCurrentPanel);
}
