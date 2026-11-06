#include "battle_03.h"

MATCH void func_801EA1A4(void) {
    u8* volatile* root;
    u8*           task;
    u8*           task2;
    u16           value_10;
    u16           value_12;

    root                = BATTLE_PANEL_ROOT_BASE;
    task                = root[-0x1E6E];
    value_10            = *(u16*)((task + 0x10));
    value_12            = *(u16*)((task + 0x12));
    task[0xF]           = 0u;
    task2               = root[-0x1E6E];
    *(u16*)((task + 4)) = value_10;
    *(u16*)((task + 6)) = value_12;
    task2[3]            = (task2[3] - 1u);
}
