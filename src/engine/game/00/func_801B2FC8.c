#include "game_00.h"

/* Active selector record func_801B5C54 returns; the item key at 0x4 is read
 * as a halfword so its high byte arrives in one load. */
typedef struct GameSelRecord {
    u8 pad_00[4];
    u8 index_04; /* bit index into the D_80145004 marks */
    u8 unk_05;
    u8 kind_06; /* ITEM_CAT_* of the selected record */
} GameSelRecord;

MATCH void func_801B2FC8(void) {
    GameSelRecord* sel;
    u8*            marks;
    u8*            item;
    s32            marked;
    s32            resource;
    s32            i;

    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        sel      = func_801B5C54();
        marks    = (u8*)&D_80145004;
        marked   = SYS_TestFlag(marks, sel->index_04);
        resource = 1;
        if (marked == 0) {
            if (sel->kind_06 == GAME_NONE) {
                D_80145034 += 1;
                if (sel->index_04 != GAME_NONE) {
                    SYS_SetFlag(marks, sel->index_04);
                }
                SND_PlayCue(EMI_CUE_ID(1, 6));
                func_801B5E58((FIELD(u16, sel, 0x4u) >> 8) * 0x28);
                /* the text row reports through its own resource; skip the dispatch */
                goto state;
            }
            item = Item_GetRecord(sel->kind_06, FIELD(u16, sel, 0x4u) >> 8);
            for (i = 0; i < 12; i++) {
                g_TextVariables[0][i] = item[i];
            }
            D_801490E4[0] = 0;
            if (Party_AddItem(sel->kind_06, FIELD(u16, sel, 0x4u) >> 8, 1, 0) & BYTE_MASK) {
                if (sel->index_04 != GAME_NONE) {
                    SYS_SetFlag(D_80145004, sel->index_04);
                    D_80145034 += 1;
                }
                SND_PlayCue(EMI_CUE_ID(1, 6));
                resource = 2;
            } else {
                resource = 3;
            }
        }
        Resource_RequestArea(resource);
    state:
        g_GameStateIndex     = GAME_REQUEST_MESSAGE;
        g_SpadWork->state_02 = 2;
    }
}
