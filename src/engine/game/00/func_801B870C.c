#include "game_00.h"

MATCH void func_801B870C(void) {
    /* INFERRED: g_Game.current is an untyped work record in this TU. Offset 0x12B is
     * a u8 flag (also written by func_801C5474). Promotion to a named field needs
     * a proven struct owner/layout from callers, strides, and field accesses. */
    g_Game.current->u.field.mode_12B.u8_value = 5;
    D_801CD36C[g_Task->unk_03]();
    func_8014D978();
}
