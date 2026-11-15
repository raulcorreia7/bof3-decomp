#include "shop_00.h"

typedef struct SceneStateCopy {
    u8 bytes[16];
} SceneStateCopy;

ASSERT_SIZE(SceneStateCopy, 0x10);

/* Save fields written over the unused bytes at SaveData+0xCA0. */
typedef struct ShopWorkRecord {
    u8        pad_00[0x8];
    u8        field_08;
    u8        field_09;
    u8        field_0A;
    u8        pad_0B;
    GameClock field_0C;
    u8        pad_10[4];
    s32       field_14;
} ShopWorkRecord;

ASSERT_SIZE(ShopWorkRecord, 0x18);

#ifdef NON_MATCHING
NON_MATCHING void SAVE_BuildSlotImage(void) {
    s32             mode;
    s32             slot;
    s32             i;
    s32             j;
    s32             name_index;
    s32             col;
    u16             n;
    u16             sum;
    u32             count;
    u8*             dst;
    u8*             src;
    u8*             src_text;
    SaveData*       work;
    ShopWorkRecord* row;

    SAVE_FormatSlot();
    func_801EF27C(1, 0x13, g_UiFormatBuffer);
    *(SceneStateCopy*)&g_SaveData.scene_state = *(SceneStateCopy*)&g_SceneState;
    j                                         = 0;
    D_80144948                                = 0;
    g_SavedScriptVars[0]                      = g_ScriptVars[0];
    g_SavedScriptVars[1]                      = g_ScriptVars[1];
    g_SavedScriptVars[2]                      = g_ScriptVars[2];
    g_SavedScriptVars[3]                      = g_ScriptVars[3];
    g_SaveEntryX                              = (u32)D_80145EC4;
    g_SaveEntryY                              = (u32)D_80145EC8;
    g_SaveAreaId                              = g_GameAreaId;
    g_SaveEntryFacing                         = g_Game.members[0].facing;
    n                                         = 0;
    j                                         = 0;
    do {
        j                                        = n;
        *(u16*)((j * 2) + (&D_801448D8 + 0xCBC)) = (u16)g_InputMasks[j];
        n                                        = n + 1;
    } while ((u32)n < 9U);
    work     = &g_SaveData;
    row      = (ShopWorkRecord*)&work->unk_C84[0x1C];
    src_text = (u8*)&work->characters[0];
    strncpy((s8*)row, (s8*)src_text, 5);
    slot = 0;
    col  = 0 & HALF_MASK;
    do {
        name_index = slot & HALF_MASK;
        if (g_PartyFieldOrder[col] == 4) {
            mode = work->emi_loaded_character_index & 0x7F;
            if ((mode != 5) && (mode != 0xC)) {
                FIELD(u8, row, col + 5) = 0xB;
            } else {
                name_index = slot & HALF_MASK;
                goto store_row; /* the kind-4 arm reaches the same store with its own index */
            }
        } else {
        store_row:
            FIELD(u8, row, name_index + 5) = (u8)g_PartyFieldOrder[name_index];
        }
        slot += 1;
        col = slot & HALF_MASK;
    } while ((u32)(slot & HALF_MASK) < 3U);
    src           = g_SceneEventFlags;
    row->field_08 = src_text[6];
    row->field_0C = work->play_clock;
    row->field_09 = work->window_style;
    row->field_0A = work->unk_7B[0];
    row->field_14 = *(s32*)(src_text + 8);
    sum           = 0;
    dst           = g_SaveBuffer;
    src           = g_SceneEventFlags - 0x650;
    i             = 0;
    row->field_14 = SYS_TestFlag(g_SceneEventFlags, 0x92U);
    D_80145025    = (u8)g_Game.flags;
    do {
        i += 1;
        count = i & HALF_MASK;
        *dst  = *src;
        dst += 1;
        sum += *src;
        src += 1;
    } while (count < SAVE_BLOCK_SIZE);
    if (count < 0x1E00U) {
        do {
            *dst = 0;
            i += 1;
            dst += 1;
        } while ((u32)(i & HALF_MASK) < 7680U);
    }
    D_800C1A70 = sum;
    if (g_SaveSlotFirst == g_SaveSlotCount) {
        g_SaveSlotCount += 1;
    }
    func_801D6CE4(g_SaveSlotFirst, (u8*)&g_SaveData);
}
#else
INCLUDE_ASM(SAVE_BuildSlotImage);
#endif
