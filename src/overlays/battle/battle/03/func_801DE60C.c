#include "battle_03.h"

MATCH void func_801DE60C(u32 slot, u8 event_type, u8 event_value, u8 group, u8 timer, u8* payload) {
    u32 offset;
    u8  flag;
    u16 half;

    offset                                      = (slot & BYTE_MASK) * 0xCu;
    half                                        = timer;
    flag                                        = g_BattleEventSlots[offset];
    g_BattleEventSlots[offset + 1u]             = event_type;
    g_BattleEventSlots[offset + 2u]             = event_value;
    g_BattleEventSlots[offset + 3u]             = group;
    g_BattleEventSlots[offset + 0xAu]           = 0u;
    g_BattleEventSlots[offset]                  = flag | 1u;
    *(u16*)((g_BattleEventSlots + offset + 8u)) = half;
    *(u32*)((g_BattleEventSlots + offset + 4u)) = payload;
}
