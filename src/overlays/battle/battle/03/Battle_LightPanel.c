#include "battle_03.h"

/* func_801EA174 */
MATCH void Battle_LightPanel(void) {
    u8* volatile* root = BATTLE_PANEL_ROOT_BASE;
    u8*           task;

    root[-0x1E6E][0xF] = 1u;
    task               = root[-0x1E6E];
    task[3]            = (task[3] + 1u);
}
