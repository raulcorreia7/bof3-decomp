#include "battle_03.h"

MATCH void func_801D71E0(void) {
    /* FAKE: volatile-drop cast lets the scheduler hoist the
     * epilogue load above the store. */
    u8* state = (u8*)&g_Battle.phase.sub_step;

    func_801DD8AC(0);
    func_801DD8AC(1);
    func_801DD8AC(2);
    Menu_ResetPanelTasks();
    EMI_LoadArchive(EMI_SLOT_AFLDKWA);
    *state = *state + 1;
}
