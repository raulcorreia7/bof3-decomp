#include "shared/etc.h"

/* Shop panel table: 0x24-byte records owned by this overlay. */
/* start_08.h cannot be included here. */
extern s8 D_8014854F;
extern s8 D_80148656;

u8 Party_CountOrder(u8 mode);

MATCH void func_801D2C7C(void) {
    u8 i;

    i = 0;
    while (i < (Party_CountOrder(PARTY_ORDER_FIELD))) {
        if (i == D_80148656) {
            g_MenuPanelTasks[i + 4].state   = 6;
            g_MenuPanelTasks[i + 0xC].state = 4;
        } else {
            g_MenuPanelTasks[i + 4].state   = 8;
            g_MenuPanelTasks[i + 0xC].state = 6;
        }
        i++;
    }
    g_MenuPanelTasks[15].state = 1;
    g_BattleChoicePhase        = 1;
    D_80148597                 = 1;
}
