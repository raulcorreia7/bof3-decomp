#include "shop_00.h"

/* Save fields written over the unused bytes at SaveData+0xCA0. */
typedef struct SaveSlotSummary {
    u8        name[CHARACTER_NAME_LENGTH];
    u8        party_order[PARTY_SLOT_COUNT];
    u8        level;
    u8        window_style;
    u8        unk_0A;
    u8        pad_0B;
    GameClock play_clock;
    u8        pad_10[4];
    s32       event_flag;
} SaveSlotSummary;

ASSERT_SIZE(SaveSlotSummary, 0x18);

#ifdef NON_MATCHING
NON_MATCHING void SAVE_BuildSlotImage(void) {
    s32              mode;
    s32              slot;
    s32              i;
    s32              j;
    s32              name_index;
    s32              col;
    u16              n;
    u16              sum;
    u32              count;
    u8*              dst;
    u8*              src;
    u16*             masks;
    SaveData*        work;
    SaveSlotSummary* row;

    SAVE_FormatSlot();
    func_801EF27C(1, 0x13, g_UiFormatBuffer);
    g_SaveData.scene_state = g_ScenarioState;
    D_80144948             = 0;
    g_SavedScriptVars[0]   = g_ScriptVars[0];
    g_SavedScriptVars[1]   = g_ScriptVars[1];
    g_SavedScriptVars[2]   = g_ScriptVars[2];
    g_SavedScriptVars[3]   = g_ScriptVars[3];
    g_SaveEntryX           = (u32)D_80145EC4;
    g_SaveEntryY           = (u32)D_80145EC8;
    g_SaveAreaId           = g_GameAreaId;
    g_SaveEntryFacing      = g_Game.members[0].facing;
    work                   = &g_SaveData;
    masks                  = (u16*)&work->unk_C84[0x38];
    n                      = 0;
    do {
        j        = n;
        masks[j] = g_InputMasks[j];
        n        = n + 1;
    } while ((u32)n < 9U);
    row = (SaveSlotSummary*)&work->unk_C84[0x1C];
    strncpy((s8*)row->name, (s8*)work->characters[0].name, CHARACTER_NAME_LENGTH);
    slot = 0;
    col  = 0 & HALF_MASK;
    do {
        name_index = slot & HALF_MASK;
        if (g_PartyFieldOrder[col] == 4) {
            mode = work->emi_loaded_character_index & 0x7F;
            if ((mode != 5) && (mode != 0xC)) {
                row->party_order[col] = 0xB;
            } else {
                name_index = slot & HALF_MASK;
                goto store_row; /* the type-4 arm reaches the same store with its own index */
            }
        } else {
        store_row:
            row->party_order[name_index] = (u8)g_PartyFieldOrder[name_index];
        }
        slot += 1;
        col = slot & HALF_MASK;
    } while ((u32)(slot & HALF_MASK) < 3U);
    row->level        = work->characters[0].level;
    row->play_clock   = work->play_clock;
    row->window_style = work->window_style;
    row->unk_0A       = work->unk_7B[0];
    sum               = 0;
    dst               = g_SaveBuffer;
    src               = (u8*)work;
    i                 = 0;
    row->event_flag   = SYS_TestFlag(g_SceneEventFlags, 0x92U);
    D_80145025        = (u8)g_Game.flags;
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
