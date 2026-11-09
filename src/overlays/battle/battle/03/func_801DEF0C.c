#include "battle_03.h"

/* re-arms the scratchpad work record for the battle view. */
MATCH void func_801DEF0C(void) {
    volatile PartyMember* work;
    volatile PartyMember* out;
    volatile PartyMember* tail;

    work                     = g_Task;
    work->unk_29             = 4;
    out                      = g_Task;
    work->unk_0C             = 0;
    work->unk_10             = 0;
    work->unk_14             = 0;
    work->unk_18             = 0;
    work->unk_1C             = 0;
    work->unk_20             = 0;
    out->facing              = g_Battle.scroll_dir;
    g_Task->unk_48           = 0;
    tail                     = g_Task;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(tail->pos.x.fixed, tail->pos.y.fixed);
    g_Task->unk_2B           = 0;
    g_Task->header.mode      = 2;
    g_Task->header.step      = 0;
    g_Task->unk_03           = 0;
    g_Task->unk_04           = 0;
}
