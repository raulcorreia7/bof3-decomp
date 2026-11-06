#include "engine/slus/slus.h"

/* writes the two record fields selected by slot and sets the mode flag.
 */
MATCH void func_8015C1A8(s32 slot, u8 field_1c, u8 field_18) {
    u32 index;
    u16 flags;

    index                                    = slot & 0xFF;
    flags                                    = g_AreaWalkFlags;
    g_BattlePartyBattlers[index].unk_18      = field_18;
    g_BattlePartyBattlers[index].unk_1C      = field_1c;
    g_AreaWalkFlags                          = flags | AREA_WALK_MAP_LOADING;
    g_BattlePartyBattlers[index].header.mode = 2;
    g_BattlePartyBattlers[index].header.step = 1;
}
