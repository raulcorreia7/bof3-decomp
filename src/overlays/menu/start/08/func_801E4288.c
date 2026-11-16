#include "start_08.h"

/* sig-kept: the retail caller passes the tile and kind as words. */
#define func_801E7720 ((void (*)(s32, u8))func_801E7720)

void func_801E7608(void);

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
