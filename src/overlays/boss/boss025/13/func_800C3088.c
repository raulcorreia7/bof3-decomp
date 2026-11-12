#include "boss025_13.h"

MATCH void func_800C3088(void) {
    u8* buf;

    func_801D8270(0x6B, 0x10);
    buf = D_801490F8;
    sprintf((char*)buf, (char*)D_800C184C, 0x15 - D_801463D0);
    UI_DrawAsciiString(0x70, 0x12, 4, buf);
    UI_DrawText(128, 18, 0, 10, D_800C32A8);

    if (D_80148603 != 0 || (D_80146329 & 0x2) != 0) {
        g_Task->header.mode -= 1;
    }
    if (g_Battle.phase.mode == BATTLE_MODE_RESULT) {
        func_801E5988();
    }
}
