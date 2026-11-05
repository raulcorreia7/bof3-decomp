#include "game_00.h"

MATCH void func_8019CBD8(void) {
    Actor* other;
    Actor* record;
    Actor* work;
    Actor* counter;

    g_SpadWork->direction_08 = 1;
    func_8015AC8C(FIELD(s32, g_AreaLoads[g_GameAreaId], 0x8u) + (g_SpadWork->unk_0B * 8));
    record                               = g_SpadWork;
    record->tint.signed_bytes.unk_5D     = -0x80;
    other                                = g_SpadWork;
    FIELD(s32, record, 0x70u)            = 1;
    other->tint.signed_bytes.unk_5E      = -0x80;
    g_SpadWork->tint.signed_bytes.unk_5F = -0x80;
    work                                 = g_SpadWork;
    work->vx                             = 0;
    work->vy                             = 0;
    work->vz                             = 0;
    work->unk_09                         = 0;
    func_8019D270();
    g_SpadWork->unk_0B = 0U;
    counter            = g_SpadWork;
    counter->unk_01    = (u8)(counter->unk_01 + 1);
    func_8015A944();
}
