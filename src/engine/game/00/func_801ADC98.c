#include "game_00.h"

MATCH s8 func_801ADC98(void) {
    s8 unit;
    s8 scaled;

    unit   = (s8)(FIELD(u8, g_Task, 0x30u) - ((u8*)&g_Game.members[0].unk_30)[0]) / 28;
    scaled = unit < 0 ? unit << 2 : unit;
    return scaled;
}
