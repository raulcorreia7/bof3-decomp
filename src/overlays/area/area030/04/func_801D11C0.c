#include "area030_04.h"

/* Copies current AREA030 settings into the active scratch record.
 * Mode 1 clears its flag and returns; otherwise a signed world value at least
 * 0x39 sets the flag to 3 before the remaining fields are copied. */
/* FAKE: retail stores the +0x54..+0x5A fields through byte-pointer views; typed stores let gcc hoist the later loads.
 */
MATCH void func_801D11C0(void) {
    if (D_80145E92[0] == 1) {
        ACTOR_CLEAR_STATE();
        return;
    }
    if (D_8014930E >= 0x39) {
        g_Task->step = 3;
    }
    g_Task->unk_2A              = D_80145EBA;
    g_Task->unk_49              = D_80145ED9;
    g_Task->unk_4A              = D_80145EDA;
    g_Task->unk_4B              = D_80145EDB;
    *(s32*)&g_Task->script      = D_80145EE0;
    *(s32*)((u8*)g_Task + 0x54) = D_80145EE4;
    *(u16*)((u8*)g_Task + 0x58) = D_80145EE8;
    *(u16*)((u8*)g_Task + 0x5A) = D_80145EEA;
    Area_AddActor();
}
