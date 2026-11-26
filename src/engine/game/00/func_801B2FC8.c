#include "game_00.h"

/* Active selector record func_801B5C54 returns; the item key at 0x4 is read
 * as a halfword so its high byte arrives in one load. */
typedef struct GameSelection {
    u8 pad_00[4];
    u8 index; /* bit index into the D_80145004 marks */
    u8 id;
    u8 category; /* ITEM_CATEGORY_* of the selected record */
} GameSelection;

MATCH void func_801B2FC8(void) {
    GameSelection* sel;
    u8*            marks;
    u8*            item;
    s32            marked;
    s32            resource;
    s32            i;

    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        sel      = func_801B5C54();
        marks    = (u8*)&D_80145004;
        marked   = SYS_TestFlag(marks, sel->index);
        resource = 1;
        if (marked == 0) {
            if (sel->category == GAME_NONE) {
                D_80145034 += 1;
                if (sel->index != GAME_NONE) {
                    SYS_SetFlag(marks, sel->index);
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                Game_RewardZenny((FIELD(u16, sel, 0x4u) >> 8) * 0x28);
                /* the text row reports through its own resource; skip the dispatch */
                goto state;
            }
            item = Item_GetRecord(sel->category, FIELD(u16, sel, 0x4u) >> 8);
            for (i = 0; i < 12; i++) {
                g_TextVariables[0][i] = item[i];
            }
            D_801490E4[0] = 0;
            if (Item_Add(sel->category, FIELD(u16, sel, 0x4u) >> 8, 1, 0) & BYTE_MASK) {
                if (sel->index != GAME_NONE) {
                    SYS_SetFlag(D_80145004, sel->index);
                    D_80145034 += 1;
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                resource = 2;
            } else {
                resource = 3;
            }
        }
        UI_MessageRequest(resource);
    state:
        g_GameStateIndex         = GAME_REQUEST_MESSAGE;
        SELF(Actor)->header.step = 2;
    }
}
