#include "boss025_13.h"

MATCH void func_800C3088(void) {
    u8* buf;

    func_801D8270(0x6B, 0x10);
    buf = D_801490F8;
    sprintf((char*)buf, (char*)D_800C184C, 0x15 - D_801463D0);
    UI_TextDrawAscii(0x70, 0x12, 4, buf);
    UI_TextDraw(128, 18, 0, 10, D_800C32A8);

    if (g_UIPanelTasks[20].state != 0 || (g_Battle.outcome.event_flags & 0x2) != 0) {
        SELF(PartyMember)->header.mode -= 1;
    }
    if (g_Battle.phase.mode == BATTLE_MODE_RESULT) {
        Effect_Reset();
    }
}
