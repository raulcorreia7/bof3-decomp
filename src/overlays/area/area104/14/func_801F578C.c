#include "area104_14.h"

MATCH void func_801F578C(void) {
    u8  index;
    s32 i;

    g_Task->direction_08 = g_Game.members[0].facing;
    func_8015AC8C(FIELD(s32, g_AreaLoads[g_GameAreaId], 0x8u) + 8);
    g_Task->tint.signed_bytes.unk_5D = -0x80;
    g_Task->tint.signed_bytes.unk_5E = -0x80;
    g_Task->tint.signed_bytes.unk_5F = -0x80;
    g_Task->header.mode += 1;
    func_801F5738();
    if ((g_GameAreaId == AREA_ID_TIDAL_CAVES_ENTRANCE) && !Item_VitalHas(VITAL_ITEM_SEA_CHARTS)) {
        return;
    }
    for (i = 0; i < 4; i++) {
        index                            = Actor_FindFreeSlot();
        g_ActorSlots[index].header.flags = 1;
        g_ActorSlots[index].type         = 0x5C;
        g_ActorSlots[index].header.mode  = 3;
        g_ActorSlots[index].unk_0A       = i << 3;
    }
}
