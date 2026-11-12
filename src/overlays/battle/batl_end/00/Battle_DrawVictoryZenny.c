#include "batl_end_00.h"

/* func_801F09F4 */
MATCH void Battle_DrawVictoryZenny(void) {
    func_801D8270(0x6E, 0x28);
    TEXT_Format(D_80149118, D_801EEC4C, g_Zenny);
    UI_DrawAsciiString(126, 42, 0, D_80149118);
    UI_DrawText(182, 42, 0, 255, D_801F0CD0);
}
