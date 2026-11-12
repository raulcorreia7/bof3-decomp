#include "boss028_16.h"

MATCH void func_800C1E80(void) {
    COORD_INT(((PartyMember*)g_Task)->pos.z) += ((PartyMember*)g_Task)->unk_14;
    ((PartyMember*)g_Task)->unk_14 += ((PartyMember*)g_Task)->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x400 to the raw register. */
    if (COORD_INT(((PartyMember*)g_Task)->pos.z) > ((s32 (*)(s32, s32))Area_SampleHeight)(((PartyMember*)g_Task)->pos.x.fixed, ((PartyMember*)g_Task)->pos.y.fixed) + 0x400) {
        COORD_INT(((PartyMember*)g_Task)->pos.z) = ((s32 (*)(s32, s32))Area_SampleHeight)(((PartyMember*)g_Task)->pos.x.fixed, ((PartyMember*)g_Task)->pos.y.fixed) + 0x400;
        ((PartyMember*)g_Task)->unk_14           = 0;
        ((PartyMember*)g_Task)->unk_20           = -0x40;
        ((PartyMember*)g_Task)->header.step--;
    }
}
