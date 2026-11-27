#include "battle_15.h"

MATCH void func_800AD71C(void) {
    volatile PartyMember* record;
    s16                   label;
    u8                    count;

    SELF(PartyMember)->unk_29 = 1;
    SELF(PartyMember)->unk_25 = 0x1E;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_24 = 0x80;
    SELF(PartyMember)->unk_27 = 0x1B;
    SELF(PartyMember)->unk_28 = 1;
    {
        PartyMember* record;
        PartyMember* other;

        record                      = SELF(PartyMember);
        record->unk_2B              = 0;
        other                       = SELF(PartyMember);
        record->unk_2C.signed_value = 2;
        other->unk_2A               = 0;
    }
    record                 = SELF(PartyMember);
    record->pos.z.fixed    = 0;
    record->screen_x.value = g_UIPanelTasks[21].pos.vx + 0x14;
    count                  = record->header.mode;
    label                  = g_UIPanelTasks[21].pos.vy;
    record->header.mode    = count + 1;
    record->screen_y.value = label + 0x12;
    Script_Select(0x13);
    Area_AddActor();
}
