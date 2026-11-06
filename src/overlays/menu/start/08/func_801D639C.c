#include "start_08.h"

MATCH void func_801D639C(void) {
    s32 input;
    s32 slot_flag;
    s32 group_index;
    s32 one;
    u8* choice;
    u8* record;
    u8  next_slot;
    u8  prev_slot;

    choice = &D_80144953;
    Menu_DrawClutStrip(*choice);
    choice += 0x15;
    record = (g_CharSlot[D_80144F5A[D_80148510]] * 0xA4) + choice;
    switch (D_8014850E) {
        case 0:
        default:
            group_index = 1;
            choice      = record + 0xE;
            break;
        case 1:
            group_index = 2;
            choice      = record + 0xF;
            break;
        case 2:
            group_index = 2;
            choice      = record + 0x10;
            break;
        case 3:
            group_index = 2;
            choice      = record + 0x11;
            break;
        case 4:
            group_index = 3;
            choice      = record + 0x12;
            break;
        case 5:
            group_index = 3;
            choice      = record + 0x13;
            break;
    }
    D_801484CC = Item_GetDescription(group_index, *choice);
    one        = 1;
    D_80148624 = 1;
    D_80148628 = D_80148508 + 6;
    D_8014862A = (D_8014850A + (D_8014850E * 0xD + 0x57));
    input      = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (input & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        next_slot  = D_8014850E + 1;
        D_8014850E = next_slot;
        if ((next_slot & BYTE_MASK) >= 6U) {
            D_8014850E = 1;
        }
    } else if (input & PADLup) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        prev_slot  = D_8014850E - 1;
        D_8014850E = prev_slot;
        if (!(prev_slot & BYTE_MASK)) {
            D_8014850E = 5;
        }
    }
    slot_flag = func_801D70EC() & BYTE_MASK;
    if (g_InputPressed & D_80145AC2) {
        if (slot_flag != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            Item_Add(group_index, *choice, 1, 0);
            *choice = 0;
            Char_RebuildStats((Character*)record);
            func_801D6E6C();
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_801485E7 = 1;
        D_80148624 = 0;
        D_8014850E = 0xFF;
        D_80148654 = 0;
        D_80148651 -= 5;
    }
}
