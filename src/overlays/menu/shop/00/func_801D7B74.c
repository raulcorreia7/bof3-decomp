#include "shop_00.h"

MATCH void func_801D7B74(void) {
    u8* state;

    state = &D_80148656;
    func_801D7E1C(state[0], 0x98, 0x3F, 0, D_8014865D);
    func_801D8050(0);
    Menu_DrawCursorFrame(0x11U, (((s8)state[0] * 0x36) + 0x3E) & 0xFFFE, 0x80, 0x34, 0U, 6);
    if (func_801D81B4(state + 5, 0xF) & 0xFF) {
        g_Characters[D_80145FCC[(s8)state[0]][0]].inoculations = 1 << (s8)D_8014865D;
        Char_RebuildStats(&g_Characters[D_80145FCC[(s8)state[0]][0]]);
        D_80148651 -= 4;
    }
}
