#include "start_08.h"

MATCH void func_801EA50C(void) {
    g_MenuStartPanel16StateFuncs[g_MenuCurrentPanel->state]();
    /* FAKE: retail reads g_CharSlot as u8[]. */
    func_801DE5D4(((u8*)g_CharSlot)[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0C]], g_MenuCurrentPanel->pos.x,
                  g_MenuCurrentPanel->pos.y, ((s32*)g_MenuCurrentPanel)[8], g_MenuCurrentPanel->flags,
                  g_MenuCurrentPanel);
}
