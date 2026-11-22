#include "battle_03.h"

/* re-arms the scratchpad work record for the battle view: sets the mode byte, clears the motion
 * accumulators, copies the pending table byte, seeds the anchor from the record's coordinates and resets the entry
 * bytes.
 */
MATCH void func_801DEF0C(void) {
    volatile PartyMember* work;
    volatile PartyMember* out;
    volatile PartyMember* tail;

    work                          = g_Task;
    work->unk_29                  = 4;
    out                           = g_Task;
    work->unk_0C                  = 0;
    work->unk_10                  = 0;
    work->unk_14                  = 0;
    work->unk_18                  = 0;
    work->unk_1C                  = 0;
    work->unk_20                  = 0;
    out->facing                   = g_Battle.scroll_dir;
    BATTLE_WORK->unk_48           = 0;
    tail                          = g_Task;
    COORD_INT(BATTLE_WORK->pos.z) = Area_HeightSample(tail->pos.x.fixed, tail->pos.y.fixed);
    BATTLE_WORK->unk_2B           = 0;
    BATTLE_WORK->header.mode      = 2;
    BATTLE_WORK->header.step      = 0;
    BATTLE_WORK->unk_03           = 0;
    BATTLE_WORK->unk_04           = 0;
}
