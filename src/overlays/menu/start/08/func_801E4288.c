#include "start_08.h"

void func_801E7608(void);
void func_801E7720(s32 tile_x, u8 tile_kind);

MATCH void func_801E4288(void) {
    u8* state;

    state      = &D_80148654;
    *state     = 0;
    D_801ED864 = 0;
    D_801ED868 = 0;
    func_801E7608();
    WinDrawCueText(70, 190, 0xA8);
    func_801E7720(0xBE, *state);
    func_801E6D88(1);
    g_MenuStartStep += 1;
}
