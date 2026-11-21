#include "battle_03.h"

MATCH void func_801DE60C(u32 slot, u8 event_type, u8 event_value, u8 group, u8 timer, u8* payload) {
    u32 offset;
    u8  flag;
    u16 half;

    offset                                          = (slot & BYTE_MASK) * 0xCu;
    half                                            = timer;
    flag                                            = g_BattleEventSlotBytes[offset];
    g_BattleEventSlotBytes[offset + 1u]             = event_type;
    g_BattleEventSlotBytes[offset + 2u]             = event_value;
    g_BattleEventSlotBytes[offset + 3u]             = group;
    g_BattleEventSlotBytes[offset + 0xAu]           = 0u;
    g_BattleEventSlotBytes[offset]                  = flag | 0x1u;
    *(u16*)((g_BattleEventSlotBytes + offset + 8u)) = half;
    *(u32*)((g_BattleEventSlotBytes + offset + 4u)) = payload;
}
