#include "start_08.h"

void func_801E7608(void);
void func_801E7720(s32 tile_x, u8 tile_kind);

MATCH void func_801E4318(void) {
    u8* step;

    func_801E7608();
    WinDrawCueText(70, 190, 0xA8);
    step = &D_80148654;
    func_801E7720(0xBE, *step);
    func_801E6D88(1);
    *step += 0x10;
    D_801ED864 += 8;
    D_801ED868 += 8;
    if (D_801ED86C == 0) {
        if (D_801ED868 >= 0x41) {
            D_801ED868 = 0x40;
        }
    } else if (D_801ED864 >= 0x41) {
        D_801ED864 = 0x40;
    }
    if (D_80148654 == 0) {
        g_MenuStartStep += 1;
    }
}
