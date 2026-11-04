#include "battle_15.h"

MATCH void func_800AD0A8(s32 enemy_index, s32 unit_index) {
    switch (BATTLE_WORK->word_08.byte.unk_08) {
        case 0:
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E2 = MEM_PTR(u8, 0x800E40BDu)[(unit_index & HALF_MASK) * 0x88];
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E3 = MEM_PTR(u8, 0x800E40BFu)[(unit_index & HALF_MASK) * 0x88];
            break;
        case 1:
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E2 = -MEM_PTR(u8, 0x800E40BDu)[(unit_index & HALF_MASK) * 0x88];
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E3 = MEM_PTR(u8, 0x800E40BFu)[(unit_index & HALF_MASK) * 0x88];
            break;
        case 2:
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E2 = -MEM_PTR(u8, 0x800E40BCu)[(unit_index & HALF_MASK) * 0x88];
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E3 = MEM_PTR(u8, 0x800E40BEu)[(unit_index & HALF_MASK) * 0x88];
            break;
        case 3:
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E2 = MEM_PTR(u8, 0x800E40BCu)[(unit_index & HALF_MASK) * 0x88];
            D_801EB630[(enemy_index & BYTE_MASK)].unk_E3 = MEM_PTR(u8, 0x800E40BEu)[(unit_index & HALF_MASK) * 0x88];
            break;
    }
}
