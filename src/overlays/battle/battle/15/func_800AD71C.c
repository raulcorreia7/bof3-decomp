#include "battle_15.h"

MATCH void func_800AD71C(void) {
    volatile PartyBattler* record;
    s16                    label;
    u8                     count;

    BATTLE_WORK->unk_29 = 1;
    BATTLE_WORK->unk_25 = 0x1E;
    BATTLE_WORK->unk_26 = 0;
    BATTLE_WORK->unk_24 = 0x80;
    BATTLE_WORK->unk_27 = 0x1B;
    BATTLE_WORK->unk_28 = 1;
    {
        PartyBattler* record;
        PartyBattler* other;

        record                     = (PartyBattler*)g_Task;
        record->unk_2B             = 0;
        other                      = (PartyBattler*)g_Task;
        record->unk_2C.signed_half = 2;
        other->unk_2A              = 0;
    }
    record              = (PartyBattler*)g_Task;
    record->pos.z.raw   = 0;
    record->unk_2E.half = D_80148628 + 0x14;
    count               = record->mode;
    label               = D_8014862A;
    record->mode        = count + 1;
    record->unk_30.half = label + 0x12;
    Actor_SelectScript(0x13);
    Area_AddActor();
}
