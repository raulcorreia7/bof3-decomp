#include "battle_03.h"

/* re-arms the scratchpad work record for the battle view: sets the mode byte, clears the motion
 * accumulators, copies the pending table byte, seeds the anchor from the record's coordinates and resets the entry
 * bytes.
 */
MATCH void func_801DEF0C(void) {
    volatile PartyMember* work;
    volatile PartyMember* out;
    volatile PartyMember* tail;

    work                                = SELF(PartyMember);
    work->unk_29                        = 4;
    out                                 = SELF(PartyMember);
    work->unk_0C                        = 0;
    work->unk_10                        = 0;
    work->unk_14                        = 0;
    work->unk_18                        = 0;
    work->unk_1C                        = 0;
    work->unk_20                        = 0;
    out->facing                         = g_Battle.scroll_dir;
    SELF(PartyMember)->unk_48           = 0;
    tail                                = SELF(PartyMember);
    COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(tail->pos.x.fixed, tail->pos.y.fixed);
    SELF(PartyMember)->unk_2B           = 0;
    SELF(PartyMember)->header.mode      = 2;
    SELF(PartyMember)->header.step      = 0;
    SELF(PartyMember)->unk_03           = 0;
    SELF(PartyMember)->unk_04           = 0;
}
