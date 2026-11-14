#include "battle_03.h"

/* func_801D9484 */
MATCH void Battle_OpenPanel(void) {
    Menu_OpenPanelTask(0u, 3u);
    D_80148332[0].mode_00 = 6;
    D_80148332[0].x_02    = 0x14;
    D_80148332[0].unk_01  = 0;
    D_80148332[0].y_04    = -0x16;
}
