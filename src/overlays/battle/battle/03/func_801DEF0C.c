#include "battle_03.h"

/* re-arms the scratchpad work record for the battle view: sets the mode byte, clears the motion
 * accumulators, copies the pending table byte, seeds the anchor from the record's coordinates and resets the entry
 * bytes.
 */
MATCH void func_801DEF0C(void) {
    volatile PartyBattler* work;
    volatile PartyBattler* out;
    volatile PartyBattler* tail;

    work                             = g_SpadWork;
    work->unk_29                     = 4;
    out                              = g_SpadWork;
    work->unk_0C                     = 0;
    work->unk_10                     = 0;
    work->unk_14                     = 0;
    work->unk_18                     = 0;
    work->unk_1C                     = 0;
    work->unk_20                     = 0;
    out->word_08.byte.facing_08      = g_BattleScrollDir;
    g_SpadWork->unk_48               = 0;
    tail                             = g_SpadWork;
    g_SpadWork->word_3C.half.span_3E = Area_SampleHeight(tail->coord_x_34.raw, tail->coord_y_38.raw);
    g_SpadWork->unk_2B               = 0;
    g_SpadWork->step_01              = 2;
    g_SpadWork->unk_02               = 0;
    g_SpadWork->unk_03               = 0;
    g_SpadWork->unk_04               = 0;
}
