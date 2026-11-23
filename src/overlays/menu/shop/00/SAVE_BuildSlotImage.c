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
    u32       exp;
    u8        event_flag;
    u8        pad_15[3];
} SaveSlotSummary;

ASSERT_SIZE(SaveSlotSummary, 0x18);

#ifdef NON_MATCHING
NON_MATCHING void SAVE_BuildSlotImage(void) {
    SaveSlotSummary* summary;
    SaveData*        work;
    Character*       leader;
    u16*             masks;
    u16              i;
    u16              sum;
    s32              mode;
    u8*              dst;
    u8*              character_index;
    u8*              src;
    u8*              flags;

    SAVE_FormatSlot();
    func_801EF27C(1, 0x13, g_UiTextFormatBuffer);
    g_SaveData.scene_state = g_ScenarioState;
    D_80144948             = 0;
    g_SavedScriptVars[0]   = g_ScriptVars[0];
    g_SavedScriptVars[1]   = g_ScriptVars[1];
    g_SavedScriptVars[2]   = g_ScriptVars[2];
    g_SavedScriptVars[3]   = g_ScriptVars[3];
    g_SaveEntryX           = (u32)g_Game.members[0].pos.x.fixed;
    g_SaveEntryY           = (u32)g_Game.members[0].pos.y.fixed;
    g_SaveAreaId           = g_GameAreaId;
    g_SaveEntryFacing      = g_Game.members[0].facing;
    i                      = 0;
    masks                  = (u16*)&g_SaveData.unk_C84[0x38];
    do {
        masks[i] = g_InputMasks[i];
        i++;
    } while (i < 9);
    work    = &g_SaveData;
    leader  = &work->characters[0];
    summary = (SaveSlotSummary*)&work->unk_C84[0x1C];
    strncpy((s8*)summary->name, (s8*)leader->name, CHARACTER_NAME_LENGTH);
    i               = 0;
    character_index = &work->emi_loaded_character_index;
    do {
        if (g_PartyFieldOrder[i] == 4 && ((mode = *character_index & 0x7F) != 5) && mode != 0xC) {
            summary->party_order[i] = 0xB;
        } else {
            summary->party_order[i] = g_PartyFieldOrder[i];
        }
        i++;
    } while (i < 3);
    flags                 = g_SceneEventFlags;
    summary->level        = leader->level;
    summary->play_clock   = work->play_clock;
    summary->window_style = work->window_style;
    summary->unk_0A       = work->unk_7B[0];
    summary->exp          = leader->exp;
    summary->event_flag   = SYS_TestFlag(flags, 0x92U);
    D_80145025            = (u8)g_Game.flags;
    sum                   = 0;
    dst                   = g_SaveBuffer;
    src                   = flags - 0x650;
    i                     = 0;
    do {
        i++;
        *dst = *src;
        dst++;
        sum += *src;
        src++;
    } while (i < SAVE_BLOCK_SIZE);
    if (i < 0x1E00) {
        do {
            *dst = 0;
            i++;
            dst++;
        } while (i < 0x1E00);
    }
    D_800C1A70 = sum;
    if (g_SaveSlotFirst == g_SaveSlotCount) {
        g_SaveSlotCount++;
    }
    func_801D6CE4(g_SaveSlotFirst, (u8*)&g_SaveData);
}
#else
INCLUDE_ASM(SAVE_BuildSlotImage);
#endif
