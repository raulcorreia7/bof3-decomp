#include "battle_03.h"

/* re-arms the scratchpad work record for the battle view: sets the mode byte, clears the motion
 * accumulators, copies the pending table byte, seeds the anchor from the record's coordinates and resets the entry
 * bytes.
 */
MATCH void func_801DEF0C(void) {
    volatile PartyBattler* work;
    volatile PartyBattler* out;
    volatile PartyBattler* tail;

    work                       = g_Task;
    work->unk_29               = 4;
    out                        = g_Task;
    work->unk_0C               = 0;
    work->unk_10               = 0;
    work->unk_14               = 0;
    work->unk_18               = 0;
    work->unk_1C               = 0;
    work->unk_20               = 0;
    out->facing                = g_BattleScrollDir;
    g_Task->unk_48             = 0;
    tail                       = g_Task;
    g_Task->pos.z.part.integer = Area_SampleHeight(tail->pos.x.fixed, tail->pos.y.fixed);
    g_Task->unk_2B             = 0;
    g_Task->mode               = 2;
    g_Task->step               = 0;
    g_Task->unk_03             = 0;
    g_Task->unk_04             = 0;
}
