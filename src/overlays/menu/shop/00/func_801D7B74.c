#include "shop_00.h"

MATCH void func_801D7B74(void) {
    u8* state;

    state = &D_80148656;
    func_801D7E1C(state[0], 152, 63, 0, D_8014865D);
    func_801D8050(0);
    Menu_DrawCursorFrame(17U, (((s8)state[0] * 0x36) + 0x3E) & 0xFFFE, 128, 52, 0U, 6);
    if (func_801D81B4(state + 5, 15) & BYTE_MASK) {
        g_Characters[g_Game.members[(s8)state[0]].character_index].inoculations = 1 << (s8)D_8014865D;
        Char_RebuildStats(&g_Characters[g_Game.members[(s8)state[0]].character_index]);
        D_80148651 -= 4;
    }
}
