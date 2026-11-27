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

/* The pad masks the save keeps at SaveData+0xCBC. */
typedef struct SaveInputMasks {
    u16 mask[9];
} SaveInputMasks;

#define SAVE_INPUT_MASKS (*(SaveInputMasks*)&g_SaveData.unk_C84[0x38])

/* The resident save image: the bytes that end where the battle-magic script table starts. */
#define SAVE_IMAGE_SIZE  0x1E00
#define SAVE_IMAGE_ADDR  (BMAGIC_SCRIPT_TABLE - SAVE_IMAGE_SIZE)

/* Fills the save summary and the saved party position, then copies the save data into the save image and sums it. */
MATCH void SAVE_BuildSlotImage(void) {
    u16              i;
    s32              mode;
    s32              sum;
    u8*              dst;
    u8*              src;
    SaveData*        work;
    SaveSlotSummary* summary;
    Character*       leader;

    SAVE_FormatSlot();
    func_801EF27C(1, 0x13, g_UITextFormatBuffer);
    g_SaveData.scene_state    = g_ScenarioState;
    g_SaveData.checksum       = 0;
    g_SaveData.script_vars[0] = g_ScriptVars[0];
    g_SaveData.script_vars[1] = g_ScriptVars[1];
    g_SaveData.script_vars[2] = g_ScriptVars[2];
    g_SaveData.script_vars[3] = g_ScriptVars[3];
    g_SaveData.entry_x        = (u32)g_Game.members[0].pos.x.fixed;
    g_SaveData.entry_y        = (u32)g_Game.members[0].pos.y.fixed;
    g_SaveData.area_id        = g_GameAreaId;
    g_SaveData.entry_facing   = g_Game.members[0].facing;
    for (i = 0; i < 9; i++) {
        SAVE_INPUT_MASKS.mask[i] = g_InputMasks[i];
    }
    work    = &g_SaveData;
    summary = (SaveSlotSummary*)&work->unk_C84[0x1C];
    leader  = &work->characters[0];
    strncpy((s8*)summary->name, (s8*)leader->name, CHARACTER_NAME_LENGTH);
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_SaveData.party.order[0][i] == 4) {
            mode = g_SaveData.emi_loaded_character_index & 0x7F;
            if (mode != 5 && mode != 0xC) {
                summary->party_order[i] = 0xB;
                continue;
            }
        }
        summary->party_order[i] = g_SaveData.party.order[0][i];
    }
    summary->level        = leader->level;
    summary->play_clock   = work->play_clock;
    summary->window_style = work->window_style;
    summary->unk_0A       = work->unk_7B[0];
    summary->exp          = leader->exp;
    summary->event_flag   = SYS_TestFlag(g_SaveData.scene_event_flags, 0x92U);
    sum                   = 0;
    dst                   = MEM_PTR(u8, SAVE_IMAGE_ADDR);
    src                   = (u8*)&g_SaveData;
    D_80145025            = (u8)g_Game.flags;
    for (i = 0; i < SAVE_BLOCK_SIZE; i++) {
        *dst++ = *src;
        sum += *src++;
    }
    for (; i < SAVE_IMAGE_SIZE; i++) {
        *dst++ = 0;
    }
    D_800C1A70 = sum;
    if (g_SaveSlotFirst == g_SaveSlotCount) {
        g_SaveSlotCount += 1;
    }
    func_801D6CE4(g_SaveSlotFirst, (u8*)&g_SaveData);
}
