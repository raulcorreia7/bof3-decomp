#include "battle_03.h"

/* integrates the local work velocity into its position fields, or
 * resets the local step when the position passes 0xFFFF, then refreshes the
 * battle update.
 */
MATCH void func_801E3398(void) {
    PartyBattler* work;

    work = g_Task;
    if ((s32)work->scale.x <= 0xFFFF) {
        work->scale.x += work->unk_0C;
        work->scale.y += work->unk_0C;
        work->unk_0C += work->unk_18;
    } else {
        work->unk_48   = 0;
        g_Task->mode   = 3;
        g_Task->step   = 0;
        g_Task->unk_03 = 0;
    }
    func_801E30F8();
}
