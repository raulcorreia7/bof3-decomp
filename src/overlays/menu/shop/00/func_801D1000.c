#include "shop_00.h"
#include "area/spad.h"

/* ACTOR_SIZE-byte work-area slots; the full record type belongs to emi/etc/game/00. */

/* Staged work-area pointer cell; a symbol-backed access keeps the store and
 * the reload on their own address load. */

/* FAKE: retail reads g_Actors as bytes. */
MATCH void func_801D1000(void) {
    u8*  slot;
    s8   index;
    u16* counter;

    index = D_8014865C;
    if (index >= 0) {
        slot = (u8*)g_Actors + index * ACTOR_SIZE;
        TASK_SET(slot);
        if ((slot[7] & 0x8) == 0) {
            slot[8] = slot[0x79];
            func_8015BAC4(g_Task->direction_08);
            slot[0x74] |= 8;
        }
        slot[0x74] &= 0xDF;
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
    }
    Menu_ResetPanelTasks();
    /* Pointer form: retail keeps one base register across the counter load and
     * the store, which a symbol access would re-materialize. */
    counter = &g_GameEntrySubstate;
    *counter += 1;
}
