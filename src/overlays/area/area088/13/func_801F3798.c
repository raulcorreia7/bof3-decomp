#include "area088_13.h"

MATCH void func_801F3798(void) {
    s8*            state;
    s16*           pos;
    s16*           at;
    WorldMapPoint* row;
    u8*            dst;
    u8*            src;
    u8*            from;
    s32            slot;
    s32            offset;
    s32            index;
    s32            count;
    s32            i;
    s32            value;
    u8             blank;
    u32            id;

    state = &D_801448EC;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            pos = &D_80145EC6;
            if ((Area_GetCellCode(pos[0], D_80145ECA) & BYTE_MASK) == 0xA1) {
                for (index = 0; index < 7; index++) {
                    if (g_GameContextSeed == D_801F6090[index][0]) {
                        break;
                    }
                }
                Message_StartAreaMessage((s16)D_801F6090[index][g_SceneState.scenario_id]);
            } else {
                at  = pos;
                row = (WorldMapPoint*)D_801F591C;
                for (;;) {
                    s16 x = at[0];

                    if (x == row->x && at[2] == row->y) {
                        break;
                    }
                    row++;
                }
                for (offset = 0, index = 0; index < 3; index++, offset += 12) {
                    if (row->unk_03 == D_801F6170[offset]) {
                        break;
                    }
                }
                count = 1;
                slot  = 0;
                dst   = (u8*)g_TextVariables;
                from  = D_801F6171 + index * 12;
            next:
                id = *from;
                if ((id & BYTE_MASK) != GAME_NONE) {
                    if (g_FishBestCatch[id & BYTE_MASK] != 0) {
                        if ((id & BYTE_MASK) == 0x16) {
                            src = D_801F6194;
                        } else {
                            src = Item_GetRecord(0, (id + 0x38) & BYTE_MASK);
                        }
                        for (i = 0; i < 12; i++) {
                            dst[i] = src[i];
                        }
                    } else {
                        blank = 0x5C;
                        for (i = 11; i >= 0; i--) {
                            dst[i] = blank;
                        }
                    }
                    /* FAKE: retail reads D_801490E4 as u8[]. */
                    ((u8*)&D_801490E4)[slot] = 0;
                    slot += 0x20;
                    dst += 0x20;
                    count++;
                    from++;
                    if (count < 12) {
                        goto next;
                    }
                }
                Message_StartAreaMessage((s16)(index + 22));
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            (*(u8*)&D_801448EC)++;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                D_801448EB = 0;
                *state     = 0;
                D_801448ED = 0;
            }
            break;
    }
}
