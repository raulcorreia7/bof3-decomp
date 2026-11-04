#include "start_08.h"

extern s8 D_80148656;

/* The stride of one D_801CA71E kind entry. */
#define START08_KIND_STRIDE 0x14

MATCH void func_801D8908(void) {
    SkillOrder* rec;
    u8*         table;
    u8*         entry;
    u8*         cursor;
    u8*         pick;
    u8          value;
    u8          next;
    u8          kind;
    u32         buttons;
    u8*         index;
    u8*         flag;

    Menu_DrawClutStrip(D_80144953);
    flag       = &D_801485C4;
    *flag      = 0;
    D_80148624 = 1;
    D_80148628 = D_80148574 + 7;
    D_8014862A = D_80148576 + ((D_8014857C * 0xD) + 0x1A);
    rec        = (SkillOrder*)((u8*)flag - DECOMP_OFFSETOF(SkillOrder, unk_54));
    index      = Party_GetAbilities(D_8014857A, D_8014857B, 0);
    pick       = index + D_8014857C;
    kind       = *pick;
    D_801484CC = *(u16*)(D_801CA71E + kind * START08_KIND_STRIDE);
    buttons    = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown | PADL1 | PADR1));
    value      = D_8014857C;
    if (buttons & PADLup) {
        if (value != 0) {
            next       = value - 1;
            D_8014857C = next;
        }
    } else if ((buttons & PADLdown) && (u8)value < 9) {
        next       = value + 1;
        D_8014857C = next;
    }
    table  = s_SkillOrderCursors[D_80148656];
    entry  = table + D_8014857B;
    *entry = D_8014857C;
    if (value != rec->cursor) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (g_InputPressed & D_80145AC2) {
        if (rec->swap_cursor == GAME_NONE) {
            if (*(Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor)) {
                SND_PlayCue(EMI_CUE_ID(1, 3));
                rec->swap_cursor = rec->cursor;
            } else {
                SND_PlayCue(EMI_CUE_ID(1, 7));
            }
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            cursor = Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->swap_cursor;
            Menu_SwapBytes_801D933C(cursor, Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor);
            rec->swap_cursor = 0xFF;
        }
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        if (rec->swap_cursor == GAME_NONE) {
            D_80148652 -= 1;
        } else {
            rec->swap_cursor = 0xFF;
        }
    }
}
