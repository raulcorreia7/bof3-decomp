#include "battle_03.h"

MATCH void func_801DE60C(u32 slot, u8 action_kind, u8 arg2, u8 arg3, u8 arg4, u8* payload) {
    u32 offset;
    u8  flag;
    u16 half;

    offset                                      = (slot & BYTE_MASK) * 0xCu;
    half                                        = arg4;
    flag                                        = g_BattleEventSlots[offset];
    g_BattleEventSlots[offset + 1u]             = action_kind;
    g_BattleEventSlots[offset + 2u]             = arg2;
    g_BattleEventSlots[offset + 3u]             = arg3;
    g_BattleEventSlots[offset + 0xAu]           = 0u;
    g_BattleEventSlots[offset]                  = flag | 1u;
    *(u16*)((g_BattleEventSlots + offset + 8u)) = half;
    *(u32*)((g_BattleEventSlots + offset + 4u)) = payload;
}
