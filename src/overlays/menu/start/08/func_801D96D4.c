#include "start_08.h"

extern volatile u8 D_801485B8; /* local: volatile access; a sibling copy is plain */
extern s8          D_8014854C; /* local: s8 read; a sibling copy is u8 */

/* gcc 2.7.2 needs the declaration form to emit the direct symbol store this function matched with. */
extern volatile u8 D_80148594; /* local: volatile access; the shared copy is plain */

MATCH void func_801D96D4(void) {
    D_80148504.active           = 0;
    g_MenuPanelTasks[14].active = 0;
    D_8014854C                  = 0;
    g_BattleChoicePanel[0]      = 0;
    g_MenuPanelTasks[17].active = 0;
    D_801485B8                  = 0;
}
