#include "area121_14.h"

MATCH void func_801F5CD0(void) {
    s32 i;
    u8  slot;

    g_Task->direction_08 = g_Game.members[0].facing;
    func_8015AC8C(FIELD(s32, g_AreaLoads[g_GameAreaId], 0x8u) + 8);
    g_Task->tint.signed_bytes.unk_5D = -0x80;
    g_Task->tint.signed_bytes.unk_5E = -0x80;
    g_Task->tint.signed_bytes.unk_5F = -0x80;
    g_Task->header.mode += 1;
    AREA_TURN_SYNC();
    if (g_GameAreaId == AREA_ID_TIDAL_CAVES_ENTRANCE && !Item_VitalHas(VITAL_ITEM_SEA_CHARTS)) {
        return;
    }
    i = 0;
    do {
        slot                            = Actor_FindFreeSlot();
        g_ActorSlots[slot].header.flags = ACTOR_FLAG_IN_USE;
        g_ActorSlots[slot].type         = 0x5C;
        g_ActorSlots[slot].header.mode  = 3;
        g_ActorSlots[slot].unk_0A       = i << 3;
        i++;
    } while (i < 4);
}
