#include "area065_13.h"

MATCH void func_801F2C6C(void) {
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

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            pos = &D_80145EC6;
            if ((Area_GetCellCode(pos[0], D_80145ECA) & BYTE_MASK) == 0xA1) {
                for (index = 0; index < 11; index++) {
                    if (g_GameContextSeed == D_801F50FC[index][0]) {
                        break;
                    }
                }
                Message_StartAreaMessage((s16)D_801F50FC[index][g_SceneState.scenario_id]);
            } else {
                at  = pos;
                row = (WorldMapPoint*)D_801F4DE0;
                for (;;) {
                    s16 x = at[0];

                    if (x == row->x && at[2] == row->y) {
                        break;
                    }
                    row++;
                }
                for (offset = 0, index = 0; index < 2; index++, offset += 6) {
                    if (row->unk_03 == D_801F525C[offset]) {
                        break;
                    }
                }
                count = 1;
                slot  = 0;
                dst   = (u8*)g_TextVariables;
                from  = D_801F525D + index * 6;
            next:
                id = *from;
                if ((id & BYTE_MASK) != GAME_NONE) {
                    if (g_FishingBestCatch[id & BYTE_MASK] != 0) {
                        if ((id & BYTE_MASK) == 0x16) {
                            src = D_801F5268;
                        } else {
                            src = Item_GetRecord(ITEM_CAT_ITEM, (id + 0x38) & BYTE_MASK);
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
                    D_801490E4[slot] = 0;
                    slot += 32;
                    dst += 0x20;
                    count++;
                    from++;
                    if (count < 6) {
                        goto next;
                    }
                }
                Message_StartAreaMessage((s16)(index + 22));
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            (*(u8*)&g_SceneEventStep)++;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode      = SCENE_EVENT_NONE;
                *state                = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
