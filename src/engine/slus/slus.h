#ifndef SLUS_004_22_H
#define SLUS_004_22_H
#define ENGINE_LOCAL_DECLS

/* The main executable's local declarations: the EMI loader, its CD and SPU
 * state, the window state and the data symbols its units share. The shared
 * subsystem headers own the cross-image names; only this executable includes
 * this file. */
#include "common/vector.h"
#include "game.h"
#include "sys/cd.h"
#include "sys/exe.h"
#include "menu/gameui.h"
#include "sys/loader_tail.h"
#include "sys/lz77.h"
#include "sys/scene.h"
#include "area/area.h"
#include "area/fishing.h"
#include "area/map.h"
#include "menu/inventory.h"
#include "menu/panel.h"
#include "scenario/party.h"
#include "menu/save.h"
#include "common/facing.h"
#include "slus/part.h"
#include "menu/save_data.h"
#include <stdio.h>
#include "common/util.h"
#include <memory.h>
#include "engine/gfx/fade/fade.h"
#include "engine/emi/loader/emi.h"
#include "engine/sound/sound.h"
#include "engine/sys/boot/boot.h"
#include "engine/state/mode/mode.h"
#include "engine/state/progress/progress.h"
#include "engine/sys/math/math.h"
#include "engine/actor/script/script.h"
#include "engine/actor/task/task.h"
#include "engine/party/character/character.h"
#include "engine/ui/text/text.h"
#include "engine/ui/message/message.h"
#include "engine/ui/menu/menu.h"
#include "engine/area/map/map.h"
#include "engine/gfx/palette/palette.h"
#include "engine/gfx/prim/prim.h"

/* Constants. */

/* Fixed retail addresses the units dereference. */
#define SCENE_TABLE_BASE           0x800E3800u          /* scene table: a u32 count, then AreaActorDef entries */
#define RESOURCE_TABLE_BASE        0x8001A000u          /* resource id table. @source: read:UI_MessageGetText@0x801502D0 */
#define RESOURCE_ID_GROUP_WORD(id) (((id) >> 12) & 0xC) /* byte offset of the group base word: id bits 14 and 15 times 4 */
#define RESOURCE_ID_INDEX(id)      ((id) & 0x3FFF)      /* index into the group's u16 offset table */
#define SLUS_LOAD_ADDRESS          0x80010000u          /* the main executable's link address */
#define AREA_CODE_BASE             0x800F5000u          /* the area code base (AreaHandlerRecord.code_base) */
#define SND_BANK_COUNT             7                    /* sound banks per layout row */
#define SND_LAYOUT_COUNT           3                    /* layout rows of the bank tables */
#define XA_STREAM_COUNT            3                    /* XA streams, each with a slot and a cue table */
#define WORD_SIGN_BIT              0x80000000u          /* the sign bit of a word */
#define COPY_KERNEL_ENTRY          ((u32) & D_8016432C) /* resume entry of the stream copy kernel */
#define MAP_ZONE_COUNT             666                  /* records in g_AreaEncounterZones */
#define MAP_ZONE_LIST_COUNT        200                  /* lists in g_EncounterZones, one per map index */
/* The tone a record reader looked up last: D_8018B40C is the tone's offset inside
 * the VAB header at `vab_header` (a word of g_SndBankHeaders). */
#define SE_TONE(vab_header)        ((VagAtr*)(D_8018B40C + (vab_header)))
#define g_SceneRecord              (*(RecordKey*)&g_ScenarioState)
#define g_CurrentActor             ((u8*)g_CurrentActor)

/* Store the row entry the menu selection picks and latch the delay it selects.
 * Kept: as an inline the row literal folds into `addiu` where retail shifts
 * first (instruction 4 differs in 4 of 4 members); the member also returns from
 * inside. */
#define SLUS_SELECT_ANSWER_MESSAGE(row, delay0, delay1)                                   \
    do {                                                                                  \
        u16 value;                                                                        \
                                                                                          \
        g_UiMessageRequest = g_AnswerMessages[(row) + g_UiMessageWindow.selection_index]; \
        switch (g_UiMessageWindow.selection_index) {                                      \
            case 0:                                                                       \
                value = (delay0);                                                         \
                break;                                                                    \
            case 1:                                                                       \
                value = (delay1);                                                         \
                break;                                                                    \
            default:                                                                      \
                return;                                                                   \
        }                                                                                 \
        g_ScriptVars[0] = (u8)value;                                                      \
    } while (0)

/* Force the word's top byte to the bundle tag and run its bundle-list entry. A
 * bare statement macro: the member declares `word`. The do/while form moves
 * bytes. Kept: as an inline the bundle tag is an argument and the mask
 * loads into $a1 instead of $v1 (2 of 2 members differ). */
#define SLUS_RETAG_BUNDLE_AND_RUN(bundle_tag)                                                         \
    word    = (*record & 0x00FFFFFF) | (bundle_tag);                                                  \
    *record = word;                                                                                   \
    func_801576FC((u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4 + (word & HALF_MASK) * 4)

/* One alias arm of a record reader: the tone table and the record table of the bank `alias`. */
#define SLUS_SE_ALIAS_ARM(alias, tones, se_records)       \
    case alias:                                           \
        D_8018B314 = SE_TONE(tones)->min;                 \
        D_8018B320 = SE_TONE(tones)->shift;               \
        D_8018B32C = SE_TONE(tones)->pan;                 \
        D_8018B324 = SE_TONE(tones)->vol;                 \
        D_8018B328 = SE_TONE(tones)->vol;                 \
        D_8018B318 = (se_records)[g_SndSeRecord * 4 + 3]; \
        break;

/* Bank record reader: loads record g_SndSeRecord of the bank's record table into voice slot 0 and fills one more slot per layer on the next voices (wrapping at 24). The head is the one body of banks 0 to 6; the alias switch that follows lets another bank supply the tone and voice. */
#define SLUS_READ_BANK_SE_HEAD(bank, se_records, tones)                                                       \
    s32 record;                                                                                               \
    s16 program;                                                                                              \
    s16 tone;                                                                                                 \
    s16 voice;                                                                                                \
                                                                                                              \
    D_8018B30C       = (bank);                                                                                \
    record           = g_SndSeRecord * 4;                                                                     \
    g_SndSeAliasBank = (se_records)[record];                                                                  \
    program          = (se_records)[record + 1] & EMI_SE_PROGRAM_MASK;                                        \
    D_8018B308       = program;                                                                               \
    g_SndSeUseVolume = (se_records)[record + 1] & EMI_SE_USE_VOLUME_FLAG;                                     \
    tone             = (se_records)[record + 2] >> 4;                                                         \
    D_8018B310       = tone;                                                                                  \
    g_SndSeRetrigger = (se_records)[record + 2] & EMI_SE_COMPARE_MASK;                                        \
    D_8018B40C       = g_VabProgramOffsets[program] + VAB_TONE_TABLE + g_VabToneOffsets[tone];                \
    D_8018B314       = SE_TONE((tones))->min;                                                                 \
    D_8018B320       = SE_TONE((tones))->shift;                                                               \
    D_8018B32C       = SE_TONE((tones))->pan;                                                                 \
    D_8018B324       = SE_TONE((tones))->vol;                                                                 \
    D_8018B328       = SE_TONE((tones))->vol;                                                                 \
    voice            = (se_records)[record + 3] & EMI_SE_VOICE_MASK;                                          \
    D_8018B318       = voice;                                                                                 \
    g_SndSeLayers    = (se_records)[record + 3] & EMI_SE_LAYER_MASK;                                          \
    if (g_SndSeLayers != 0) {                                                                                 \
        g_SndSeLayers = g_SndSeLayers >> 5;                                                                   \
        switch (g_SndSeLayers) {                                                                              \
            case 3:                                                                                           \
                D_8018B380 = (se_records)[g_SndSeRecord * 4 + 1] & EMI_SE_PROGRAM_MASK;                       \
                D_8018B388 = D_8018B310 + g_SndSeLayers;                                                      \
                D_8018B38C = D_8018B314;                                                                      \
                D_8018B398 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B380] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B388]; \
                D_8018B39C = SE_TONE((tones))->vol;                                                           \
                D_8018B3A0 = SE_TONE((tones))->vol;                                                           \
                D_8018B3A4 = SE_TONE((tones))->pan;                                                           \
                D_8018B390 = D_8018B318 + 3;                                                                  \
                if (D_8018B390 >= 24) {                                                                       \
                    D_8018B390 = D_8018B318 + 3 - 24;                                                         \
                }                                                                                             \
            case 2:                                                                                           \
                D_8018B358 = (se_records)[g_SndSeRecord * 4 + 1] & EMI_SE_PROGRAM_MASK;                       \
                D_8018B360 = D_8018B310 + g_SndSeLayers;                                                      \
                D_8018B364 = D_8018B314;                                                                      \
                D_8018B370 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B358] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B360]; \
                D_8018B374 = SE_TONE((tones))->vol;                                                           \
                D_8018B378 = SE_TONE((tones))->vol;                                                           \
                D_8018B37C = SE_TONE((tones))->pan;                                                           \
                D_8018B368 = D_8018B318 + 2;                                                                  \
                if (D_8018B368 >= 24) {                                                                       \
                    D_8018B368 = D_8018B318 + 2 - 24;                                                         \
                }                                                                                             \
            case 1:                                                                                           \
                D_8018B330 = (se_records)[g_SndSeRecord * 4 + 1] & EMI_SE_PROGRAM_MASK;                       \
                D_8018B338 = D_8018B310 + g_SndSeLayers;                                                      \
                D_8018B33C = D_8018B314;                                                                      \
                D_8018B348 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B330] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B338]; \
                D_8018B34C = SE_TONE((tones))->vol;                                                           \
                D_8018B350 = SE_TONE((tones))->vol;                                                           \
                D_8018B354 = SE_TONE((tones))->pan;                                                           \
                D_8018B340 = D_8018B318 + 1;                                                                  \
                if (D_8018B340 >= 24) {                                                                       \
                    D_8018B340 = D_8018B318 + 1 - 24;                                                         \
                }                                                                                             \
                break;                                                                                        \
        }                                                                                                     \
    }

/* The record reader of banks 0, 4, 5 and 6, whose alias banks are 1 to 3. */
#define SLUS_READ_BANK_SE(bank, se_records, tones)                    \
    SLUS_READ_BANK_SE_HEAD(bank, se_records, tones)                   \
    if (g_SndSeAliasBank != 0) {                                      \
        D_8018B30C = g_SndSeAliasBank & EMI_SE_ALIAS_MASK;            \
        switch (D_8018B30C) {                                         \
            SLUS_SE_ALIAS_ARM(1, g_SndBankHeaders[1], g_SndBankSe[1]) \
            SLUS_SE_ALIAS_ARM(2, g_SndBankHeaders[2], g_SndBankSe[2]) \
            SLUS_SE_ALIAS_ARM(3, g_SndBankHeaders[3], g_SndBankSe[3]) \
        }                                                             \
    }

/* Types. */

/* The text, panel and cue handlers share this state block. */
typedef struct MenuState {
    Pos2u text;
    Pos2u origin;
    u8    step_id;         /* 0x08 */
    u8    panel_index;     /* 0x09 */
    s8    last_row;        /* 0x0A */
    s8    selection_index; /* 0x0B */
    s16   cue_counter;     /* 0x0C */
    s16   cue_timer;       /* 0x0E */
} MenuState;

ASSERT_OFFSET(MenuState, text, 0x00);
ASSERT_OFFSET(MenuState, origin, 0x04);
ASSERT_OFFSET(MenuState, step_id, 0x08);
ASSERT_OFFSET(MenuState, panel_index, 0x09);
ASSERT_OFFSET(MenuState, last_row, 0x0A);
ASSERT_OFFSET(MenuState, selection_index, 0x0B);
ASSERT_OFFSET(MenuState, cue_counter, 0x0C);
ASSERT_OFFSET(MenuState, cue_timer, 0x0E);
ASSERT_SIZE(MenuState, 0x10);

/* The spill offsets and the 0x40 extent are retail reads: the decoder stores s0-s7 with `sw s0..s7, 0x20..0x3C($t0)` on the context base. */
typedef struct EMIDecodeContext {
    u8* dst;        /* 0x00 decompressed output cursor */
    u32 unk_04;     /* 0x04 not referenced by the decoder */
    u8* src;        /* 0x08 input cursor; match source while state is 12 */
    u32 unk_0C;     /* 0x0C cleared by the initialiser, never read */
    u32 state;      /* 0x10 resume state, stored as state * 4 (table offset) */
    u32 pending;    /* 0x14 saved control byte or pending run length */
    u8* limit;      /* 0x18 end of the scratchpad input window */
    u8* copy_entry; /* 0x1C copy-kernel resume entry (0x8016432C) */
    u32 spill[8];   /* 0x20-0x3C outer caller s0-s7, reloaded by func_801642CC */
} EMIDecodeContext;

ASSERT_OFFSET(EMIDecodeContext, spill, 0x20);
ASSERT_SIZE(EMIDecodeContext, 0x40);

typedef struct PanelSortDepth {
    s32 depth;        /* 0x00 - z and z0 as one word; bit 31 tags a live row */
    u8  pad_04[0x08]; /* 0x04-0x0B */
} PanelSortDepth;

ASSERT_SIZE(PanelSortDepth, 0xC);

/* The SPU voice record the sound units index: _SsReadDeltaValue walks the byte
 * stream through cursor at +0x04 and accumulates at +0x80, _SsVmSetSeqVol sets
 * the rate byte at +0x12 and the volume/pan pair at +0x74/+0x76. Both models
 * end at 0xAC; the fields they cover do not overlap, so one record keeps both
 * spellings and the bytes between them stay unnamed. */
typedef struct SoundVoice {
    u8  pad_00[4];    /* +0x00 */
    u8* cursor;       /* +0x04 byte stream cursor */
    u8  pad_08[0x0A]; /* +0x08 */
    u8  rate;         /* +0x12 */
    u8  pad_13[0x61]; /* +0x13 */
    u16 vol;          /* +0x74 */
    u16 pan;          /* +0x76 */
    u8  pad_78[8];    /* +0x78 */
    s32 accum;        /* +0x80 */
    u8  pad_84[0x28]; /* +0x84 */
} SoundVoice;

/* Stack snapshots of the fixed dispatch tables the step handlers copy to the frame and index: UI_MessageDispatchState/func_801510DC copy the eight-entry tables at g_UiMessageStateSteps/D_80149A7C, func_80151538/UI_MessageDispatchChoiceMode the six-entry tables at D_80149A9C/g_UiMessageChoiceModes, func_8015196C/func_80151A98 build the two-entry tables on the stack, and g_UiMessageSteps is the sixteen-entry handler table UI_MessageDispatchStep copies. */
typedef struct {
    Callback steps[8];
} MessageStateSteps;

typedef struct {
    Callback steps[6];
} MessageChoiceSteps;

typedef struct {
    Callback steps[2];
} ChoiceSteps;

typedef struct {
    Callback steps[16];
} MessageSteps;

typedef struct MenuPanelFuncs {
    Callback handlers[9];
} MenuPanelFuncs;

ASSERT_SIZE(MenuPanelFuncs, 0x24);

typedef struct MenuPanelModes {
    void (*modes[3])(void);
} MenuPanelModes;

ASSERT_SIZE(MenuPanelModes, 0x0C);

typedef struct MenuPanelSteps {
    void (*steps[5])(void);
} MenuPanelSteps;

ASSERT_SIZE(MenuPanelSteps, 0x14);

typedef struct EmiRingSteps {
    u32 steps[6];
} EmiRingSteps;

ASSERT_SIZE(EmiRingSteps, 0x18);

typedef void (*BundleOpcodeCallback)(void* record);
typedef void (*CellDrawCallback)(u8* record, s32 cell_x, s32 cell_y);

/* Record of the D_8017F5B4 table; no field meaning is proven. */
typedef struct {
    u8  unk_00;
    u8  unk_01;
    s16 unk_02;
} Rec_8017F5B4;

ASSERT_SIZE(Rec_8017F5B4, 0x04);

/* Row of the D_8017F960 panel table: tile column offset, tile row offset and
 * the row step multiplied by the panel index; read through the interior symbols
 * D_8017F962 and D_8017F964 by UI_MessageDrawPresetRows and UI_MessageDrawPresetCursor. */
typedef struct {
    s16 col_offset;
    s16 row_offset;
    s16 scale;
} WindowTextRow;

ASSERT_SIZE(WindowTextRow, 0x06);

/* The bank records at g_EmiBanks seen from its second symbol, 0x80146780 (EMIBank + 4):
 * EMI_VabLoadHeader and SND_SetBankLayout reach it through this symbol and a typed
 * EMIBank access moves their register allocation. */
typedef struct EMIAudioLink {
    u32 word;
    u8  unk_04[8];
    u16 index;
    u16 state;
    u8  unk_10[4];
} EMIAudioLink;

/* The selected record byte at 0x80146870/0x80146874: the equality and order
 * tests read it unsigned, the getter returns it sign-extended. */
typedef union RecordKey {
    s8 sbyte; /* 0x00 */
    u8 ubyte; /* 0x00 */
} RecordKey;

/* The six-byte panel row view that starts at row +2: its last halfword is the
 * next row's +0. UI_MessageDrawPresetCursor indexes it by the selection byte. */
typedef struct PanelRowWindow {
    s16 row_offset;
    s16 scale;
    u16 next_row_first;
} PanelRowWindow;

/* The loader cursor cell 0x80146844: the header scan walks it by byte, the
 * transfer path indexes it by the 0x10-byte slot. */
typedef union OverlaySlotCursor {
    u8*          bytes; /* 0x00 */
    EMITocEntry* slots; /* 0x00 */
} OverlaySlotCursor;

typedef s8 (*ActorMovementCallback)(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);

/* Data. */

/* Retail data D_80180000-D_801DFFFF and scratchpad (one declaration each). */
extern u8  D_1F800004;
extern u32 D_1F80000C;

/* One list of the cell ordering table: its first and its last packet. */
typedef struct AreaCellPacketList {
    P_TAG* head;
    P_TAG* tail;
} AreaCellPacketList;

/* D_80142CC0 as lists: six per grid row. */
extern AreaCellPacketList g_AreaCellPacketLists[][6];
/* Retail data below D_80145000 (one declaration each). */
extern s32                D_80010004;
extern EMIDecodeContext   D_800327A0[];
extern u8                 D_800E3800;

extern u8                    D_80142CC0[];
extern u8                    D_80142CE0[];
/* D_80143740 */
extern u32                   g_AreaCellPackets[];
/* SLUS-only state: overlays declare these addresses with their own views, so
 * the registry does not emit them; g_SysThreads stays in sys/sched.h. */
extern u_long                D_80143DB8;
extern struct XF_HDR         g_LogoHeader;
extern u8                    D_80143F48[];
extern s16                   g_ScrollHeight[]; /* low half (+2) of the big-endian 0x80143F84 scroll word */
extern s32                   D_80144967;
/* Retail data D_80145000-D_80146FFF (one declaration each). */
extern s32                   D_80145030;
extern u32                   g_GfxLayerLinks[][GFX_LAYER_COUNT];
/* D_801459D0 */
extern u32*                  g_GfxOtHeads[GFX_LAYER_COUNT];
extern void*                 g_SysSectorBuffer;
extern u32                   g_GfxUploadCursor;
extern u16                   D_80145A54[];
/* Pad repeat decoder state words; shop also reads them (func_801D5D98). */
/* Text cursor cells: the draw-text entry seeds them and the line printer
 * computes with them. */
extern u16                   D_80145ACA;
extern u16                   D_80145ACC;
extern s32                   D_80145DA0;
extern u8                    D_80145E9B[];
extern s32                   D_80145EC4;
extern u8                    D_8014626C[];
extern volatile u32          g_EmiStartSector;
extern volatile u32          g_EmiBytesLeft;
extern volatile u32          g_EmiLoadArg;
extern volatile u32          g_EmiFirstWord;
extern volatile u16          g_EmiEntryType;
extern volatile u32          g_EmiRingBase;
extern u32                   g_EmiStep;
/* D_80146474 */
extern s32                   g_EmiUploadBytesLeft;
extern volatile u32          D_80146478;
extern volatile u8           g_EmiReadStatus;
extern volatile u8           g_EmiNextSlot;
/* D_80146482 */
extern u8                    g_EmiUploadBank;
/* D_80146483 */
extern u8                    g_EmiEntryBank;
extern volatile u8           D_80146484;
extern volatile u8           D_80146485;
extern volatile u8           D_80146486;
/* D_80146488 */
extern s8                    g_EmiRingIndex;
extern s8                    g_EmiRingSlot;
/* D_8014648A */
extern s8                    g_CdState;
extern s8                    D_8014648B;
/* D_8014648C */
extern s32                   g_CdSyncStatus;
extern u16                   g_EmiStreamIdleFrames;
/* D_80146492 */
extern u16                   g_EmiSeekRetries;
extern u8                    g_EmiStreamState;
/* D_80146498 */
extern u8                    g_EmiSyncResult[];
extern volatile u8           g_EmiRingStates[];
extern s32                   D_80146518[];
extern u32                   g_EmiSlotSectors[];
extern EMIBank               g_EmiBanks[SND_BANK_COUNT];
/* D_80146780 */
extern volatile EMIAudioLink g_EmiBankLinks[];
/* FAKE: SND_SetBankLayout stores the bank records, headers and SE tables through their own symbols;
 * the g_EmiBanks, g_SndBankHeaders and g_SndBankSe views share one base register and shrink it. */
/* D_80146784 */
extern u8*                   g_EmiBank0SeRecords;
/* D_80146788 */
extern u32                   g_EmiBank0SequenceBuffer[];
/* D_8014678C */
extern s16                   g_EmiBank0VabId;
/* D_80146790 */
extern s32                   g_EmiBank1SpuAddress;
/* D_80146794 */
extern s32                   g_EmiBank1VabHeader;
/* D_80146798 */
extern u8*                   g_EmiBank1SeRecords;
/* D_8014679C */
extern s32                   g_EmiBank1SequenceBuffer;
/* D_801467A0 */
extern u16                   g_EmiBank1VabId;
/* D_801467A4 */
extern s32                   g_EmiBank2SpuAddress;
/* D_801467A8 */
extern s32                   g_EmiBank2VabHeader;
/* D_801467AC */
extern u8*                   g_EmiBank2SeRecords;
/* D_801467B0 */
extern s32                   g_EmiBank2SequenceBuffer;
/* D_801467B4 */
extern u16                   g_EmiBank2VabId;
/* D_801467B8 */
extern s32                   g_EmiBank3SpuAddress;
/* D_801467BC */
extern s32                   g_EmiBank3VabHeader;
/* D_801467C0 */
extern u8*                   g_EmiBank3SeRecords;
/* D_801467C4 */
extern s32                   g_EmiBank3SequenceBuffer;
/* D_801467C8 */
extern u16                   g_EmiBank3VabId;
/* D_801467CC */
extern s32                   g_EmiBank4SpuAddress;
/* D_801467D0 */
extern s32                   g_EmiBank4VabHeader;
/* D_801467D4 */
extern u8*                   g_EmiBank4SeRecords;
/* D_801467D8 */
extern s32                   g_EmiBank4SequenceBuffer;
/* D_801467DC */
extern u16                   g_EmiBank4VabId;
/* D_801467E0 */
extern s32                   g_EmiBank5SpuAddress;
/* D_801467E4 */
extern s32                   g_EmiBank5VabHeader;
/* D_801467E8 */
extern u8*                   g_EmiBank5SeRecords;
/* D_801467EC */
extern s32                   g_EmiBank5SequenceBuffer;
/* D_801467F0 */
extern u16                   g_EmiBank5VabId;
/* D_801467F4 */
extern s32                   g_EmiBank6SpuAddress;
/* D_801467F8 */
extern s32                   g_EmiBank6VabHeader;
/* D_801467FC */
extern u8*                   g_EmiBank6SeRecords;
/* D_80146800 */
extern s32                   g_EmiBank6SequenceBuffer;
/* D_80146804 */
extern u16                   g_EmiBank6VabId;
extern u8                    D_801486A0[];
extern u8                    D_8014871C[];
extern u8                    D_80148798[];
extern u8                    D_80148814[];
extern u8                    D_80148890[];
extern u8                    D_8014890C[];
extern u8                    D_80148988[];
/* D_80148A18 */
extern s32                   g_SndBank0Header;
/* D_80148A1C */
extern s32                   g_SndBank1Header;
/* D_80148A20 */
extern s32                   g_SndBank2Header;
/* D_80148A24 */
extern s32                   g_SndBank3Header;
/* D_80148A28 */
extern s32                   g_SndBank4Header;
/* D_80148A2C */
extern s32                   g_SndBank5Header;
/* D_80148A30 */
extern s32                   g_SndBank6Header;
/* D_80148A34 */
extern s32                   g_SndBank0Sequence;
/* D_80148A38 */
extern s32                   g_SndBank1Sequence;
/* D_80148A3C */
extern s32                   g_SndBank2Sequence;
/* D_80148A40 */
extern s32                   g_SndBank3Sequence;
/* D_80148A44 */
extern s32                   g_SndBank4Sequence;
/* D_80148A48 */
extern s32                   g_SndBank5Sequence;
/* D_80148A4C */
extern s32                   g_SndBank6Sequence;
extern volatile u32          g_EmiSectorCursor;
extern s32                   D_8014680C;
extern s32                   D_80146810;
extern s32                   D_80146814;
extern s16                   D_80146818;
extern u16                   D_8014681A;
extern u16                   D_8014681C;
extern u16                   D_8014681E;
extern u16                   D_80146820;
extern u8                    D_80146824[];
extern s8                    D_8014682C;
extern s8                    D_8014682E;
extern s8                    D_8014682F;
extern u8                    g_SndCDVolume;
extern s8                    D_80146832;
extern u8                    D_80146834;
extern u8                    D_80146835;
extern CdlATV                g_SndCDMix;
extern u8                    g_EmiStreamMode;
extern OverlaySlotCursor     D_80146844;
extern u32*                  D_80146848;
/* D_8014684C */
extern RECT                  g_EmiUploadRect;
extern u8                    D_80146855;
extern u8                    D_80146856;
extern volatile u32          D_80146858;
extern volatile u32          D_8014685C;
/* Retail data D_80147000-D_8014FFFF (one declaration each). */
extern PanelSortItem         D_80147CFC[];
extern PanelSortItem         D_80147D08[]; /* == &D_80147CFC[1] */
extern PanelSortDepth        D_80147D0C[]; /* == &D_80147CFC[1].depth */
extern MATRIX                D_801481B8;
extern CameraAngle           D_801481D8;
extern u16                   D_801481E0;
extern s32                   D_801481F0;
extern s32                   D_801481F4;
extern s32                   D_80148200;
extern u8                    D_8014820C;
/* The work-record table: func_8014D4E0 appends g_Task, func_8014BB20 sorts it by the s16 at +0x3E. */
extern Actor*                D_80148214[];
/* D_8014828C */
extern s32                   g_AreaGridActors[];
extern u8                    D_80148332[];
extern u8                    D_8014865B;
extern u8                    g_SndBankSe[SND_BANK_COUNT][124];
extern u16                   D_80148A04;
extern u16                   D_80148A06;
extern u16                   D_80148A0C;
extern u16                   D_80148A0E;
extern s32                   g_SndBankHeaders[SND_BANK_COUNT];
extern s32                   g_SndBankSequences[SND_BANK_COUNT];
extern u16                   D_80149010[];
extern u16                   D_80149040[];
extern u16                   D_80149070[];
/* D_801490A3 */
extern u8                    g_UiMessageChoiceStep;
/* D_801490AC */
extern u32                   g_UiMessageScript;
extern u8*                   D_801490B0;

/* The message window with the byte ahead of it: UI_TextDrawGlyph reads both through this one block. */
typedef struct MessageWindowBlock {
    u8        row_offset_index; /* 0x00 - row of g_TextRowOffsets the glyph height uses */
    u8        pad_01[3];        /* 0x01-0x03 */
    MenuState window;           /* 0x04 - g_UiMessageWindow */
} MessageWindowBlock;

extern u8                          D_801490B8[]; /* base form: UI_TextDrawGlyph takes its address and reads [0] */
extern u8                          D_801490B9;
extern s8                          D_801490BA[];
extern u8                          D_801490BB[];
/* D_801490BC */
extern MenuState                   g_UiMessageWindow;
extern s16                         D_801490C8; /* cue counter; reads sign at the < 9 test and zero-extends elsewhere */
extern s16                         D_801490CA;
extern u8                          D_801490CE;
extern s32                         D_801490D7;
extern s32                         D_801492FC;
extern s32                         D_80149300;
extern s32                         D_80149304;
extern u16                         D_80149336;
/* D_8014933D */
extern u8                          g_AreaCellPacketCount;
/* D_80149340 */
extern u8                          D_80149341;
extern const char                  g_ExceptionHexFormat[];
extern const u32                   g_UiModeLocals[];
/* D_80149A5C */
extern const MessageStateSteps     g_UiMessageStateSteps;
extern const MessageStateSteps     D_80149A7C;
extern const MessageChoiceSteps    D_80149A9C;
/* D_80149AB4 */
extern const MessageChoiceSteps    g_UiMessageChoiceModes;
/* The 16-entry handler table (code addresses 0x80152370..0x801526C8, the step
 * handlers that follow UI_MessageDispatchStep): the shared step byte's indices at and
 * above 0x80 dispatch through it. */
/* D_80149ACC */
extern const MessageSteps          g_UiMessageSteps;
/* D_80149B30 */
extern const struct MenuPanelModes g_UiMessagePanelModes;
/* D_80149B3C */
extern const struct MenuPanelSteps g_UiMessageWindowSteps;
/* D_80149B50 */
extern const struct MenuPanelSteps g_UiMessageChoiceSteps;
/* D_80149B64 */
extern const struct MenuPanelSteps g_UiMessagePresetSteps;
extern const VECTOR                D_80149BF0;
extern const Callback              g_CdStateHandlers[CD_STATE_COUNT];
extern const EmiRingSteps          g_EmiRingSteps;
extern const char                  D_80149F9C[];
extern const char                  D_80149FAC[];
extern const u32                   D_8014AAB8[4];
extern u8                          D_8016432C;
/* D_8017F44C */
extern const char                  D_8017F44C[];
extern const void* const           g_ExceptionNames[];
/* Retail data D_80170000-D_8017FFFF (one declaration each). */
extern const u16                   s_DefaultInputMasks[10];
extern const Rec_8017F5B4          D_8017F5B4[27];
/* D_8017F628 */
extern const u16                   g_AnswerMessages[32];
extern const CellDrawCallback      D_8017F668[77];
extern const s16                   D_8017F7A8[54];
extern const s16                   D_8017F814[54];
extern const u16                   D_8017F880[10];
extern const u32                   D_8017F8E0[4];
/* D_8017F8F0 */
extern const BundleOpcodeCallback  g_BundleOpcodes[7];
extern u8                          D_8017F91C;
extern u8                          D_8017F91D;
extern const u16                   D_8017F92C[2];
extern const u16                   D_8017F930[10];
extern const u16                   D_8017F944[7][2];
extern u16                         D_8017F946;
extern const WindowTextRow         D_8017F960[3];
extern PanelRowWindow              D_8017F962[];
extern s16                         D_8017F964;
extern const u16                   D_8017F972;
extern const EncounterZone         g_AreaEncounterZones[MAP_ZONE_COUNT];
/* D_80181164 */
extern const EncounterZone* const  g_EncounterZones[MAP_ZONE_LIST_COUNT];
/* D_80181484 */
extern const SceneFlagPair         g_SceneFlagPairs[SCENE_FLAG_COUNT];
extern const ScriptEntry           D_80181BDC[40];
extern const ScriptEntry* const    D_80181C7C[11];
extern const BGMTrack              g_BGMTracks[BGM_TRACK_COUNT];
extern u8                          D_80182174;
extern u8                          D_80182175;
extern u8                          D_80182176;
extern u8                          D_80182177;
extern s32                         D_801821D0;
/* The readers resolve a tone through `g_SndBankHeaders[bank]`: one header pointer
 * per bank, installed by `SND_SetBankLayout` (`0x80161808`). The reader indexes
 * the header at `0x820 + 512*program + 32*tone` and copies the tone's volume,
 * pan, pitch tune and min note into voice state.
 *
 * The shipped tables make the address more than that formula. The program
 * offset table `0x801821E0` holds four halfwords `{0, 512, 1024, 0}`, and the
 * readers index it with the record's program 0-7. Program 3 therefore reads 0,
 * and programs 4-7 read the first tone-table halfwords (0, 32, 64, 96), so the
 * slot is not `512 * program`. The quirk affects 1,248 entries, all bank 6
 * programs 3-7 in the 200 `BIN/BENEMY` banks. It is shipped-engine behavior, not
 * the record's meaning. */
extern u16                         g_VabProgramOffsets[4];
extern u16                         g_VabToneOffsets[80];
extern u16                         g_SndVolumeLevels[80];
extern s8                          D_8018232A;
/* D_80182348 */
extern u32                         g_SndBankSpuAddress[SND_LAYOUT_COUNT][SND_BANK_COUNT];
/* D_8018239C */
extern u32                         g_SndBankHeaderSize[SND_LAYOUT_COUNT][SND_BANK_COUNT];
/* D_801823F0 */
extern u32                         g_SndBankSequenceSize[SND_LAYOUT_COUNT][SND_BANK_COUNT];
extern DiscLba                     g_EmiSlotLbas[EMI_SLOT_COUNT + 1];
/* D_80183230 */
extern u32                         g_XAStreamSlots[XA_STREAM_COUNT];
/* D_8018323C */
extern u32                         g_XACues[XA_STREAM_COUNT];
extern u32                         g_EmiEntryTypes[11];
extern void (*g_XAStates[SND_XA_STATE_COUNT])(void);
extern u16          g_XACueStream2[22];
extern u16          g_XACueStream1[896];
extern u16          g_XACueStream0[20];
extern u32          D_801839EC[12];
extern u32          D_80183A1C[17];
extern u32          D_80183A60[4];
extern u16          D_80183A70[];
extern u32          g_SysStartupReturn; /* start of the BSS stup2 clears */
extern u8           D_8018B2F4;
extern s16          D_8018B308;
extern s16          D_8018B30C;
extern s16          D_8018B310;
extern s16          D_8018B314;
extern s16          D_8018B318;
/* The four front-end selection voice slots sit in one 0x28-byte-strided block
 * (D_8018B308 + 0x28 * k, k = 0-3); +0x14 of a slot holds the voice number its
 * cue keys on, which is what the four symbols below name. The state word
 * func_8015D71C fills packs only that number's low byte, so the packing reads
 * take the halfword's low byte. */
extern s16          D_8018B31C;
extern s16          D_8018B320;
extern s16          D_8018B324;
extern s16          D_8018B328;
extern s16          D_8018B32C;
extern s16          D_8018B330;
extern s16          D_8018B338;
extern s16          D_8018B33C;
extern s16          D_8018B340;
extern s16          D_8018B344;
extern s16          D_8018B348;
extern s16          D_8018B34C;
extern s16          D_8018B350;
extern s16          D_8018B354;
extern s16          D_8018B358;
extern s16          D_8018B360;
extern s16          D_8018B364;
extern s16          D_8018B368;
extern s16          D_8018B36C;
extern s16          D_8018B370;
extern s16          D_8018B374;
extern s16          D_8018B378;
extern s16          D_8018B37C;
extern s16          D_8018B380;
extern s16          D_8018B388;
extern s16          D_8018B38C;
extern s16          D_8018B390;
extern s16          D_8018B394;
extern s16          D_8018B398;
extern s16          D_8018B39C;
extern s16          D_8018B3A0;
extern s16          D_8018B3A4;
/* D_8018B3D8 */
extern s16          g_SndSeVolumeL;
/* D_8018B3DC */
extern s16          g_SndSeVolumeR;
/* D_8018B3E0 */
extern s16          g_SndSeAliasBank;
/* D_8018B3E4 */
extern s16          g_SndSeLayers;
/* D_8018B3E8 */
extern s16          g_SndSeRetrigger;
/* D_8018B3EC */
extern s16          g_SndSeLastRetrigger;
/* D_8018B3F0 */
extern s16          g_SndSeLastVoice;
/* D_8018B3F4 */
extern s16          g_SndSeUseVolume;
/* D_8018B404 */
extern u16          g_SndSeRecord;
/* D_8018B408 */
extern u16          g_SndSeBank;
extern u16          D_8018B40C;
extern s32          D_8018B410;
extern s32          D_8018B414;
extern u16          D_8018B418;
extern u16          D_8018B41A;
extern SpuVoiceAttr D_8018B450;
extern s32          D_8018B454;
extern u16          D_8018B458;
extern u16          D_8018B45A;
extern CdlLOC       D_8018B490;
/* D_8018B4A0 */
extern u8           g_EmiVramType;
/* D_8018B4A4 */
extern u8           g_EmiVramRow;
/* D_8018B4A8 */
extern u8           g_EmiVramEntryCount;
/* D_8018B4AC */
extern u8           g_EmiVramStep;
extern u32          D_8018B4B0;
extern void (*D_8018E7D4)(s16 voice);
extern void (*D_8018E988)(s16 voice);
extern s8                   D_8018E98C;
extern u32                  D_80190C60; /* end of the BSS stup2 clears */
extern u8                   D_801C839C[];
extern u8                   D_801C839D[];
extern ActorModeCallback    D_801C83D8[];
extern u8*                  g_ItemCategoryIds[];
extern u8*                  g_ItemCategoryCounts[];
/* Ability elements and flags share a 16-bit mask in this image. */
extern u16                  D_801CA71C;
/* The scratchpad work cell. Not volatile: 37 matched SLUS readers keep the
 * pointer in a register across a block (func_8015AD00 at +0xBC), and a volatile
 * cell adds a reload there. A unit that must reload it after a call assigns it
 * to a local at the call boundary. */
extern u8                   D_801EFEFC;
extern u8                   D_801F016C;
extern u8                   D_801F0488;
extern u8                   D_801F0778;
extern u8                   D_801F2C18;
extern u8                   D_801F2C3C;
extern u8                   D_801F2C64;
extern u8                   D_801F2C94;
extern u8                   D_801F2C9C;
extern u8                   D_801F2CA4;
extern u8                   D_801F2CB0;
extern u8                   D_801F2CD0;
extern u8                   D_801F2D10;
extern u8                   D_801F2D20;
extern u8                   D_801F2DCC;
extern u8                   D_801F2DD4;
extern u8                   D_801F2DD8;
extern u8                   D_801F2DE0;
extern u8                   D_801F2E0C;
extern u8                   D_801F2E24;
extern u8                   D_801F2E54;
extern u8                   D_801F2EC4;
extern u8                   D_801F2EC8;
extern u8                   D_801F2F78;
extern u8                   D_801F2F7C;
extern u8                   D_801F2FA0;
extern u8                   D_801F2FFC;
extern u8                   D_801F3048;
extern u8                   D_801F3058;
extern u8                   D_801F30AC;
extern u8                   D_801F30B0;
extern u8                   D_801F30C0;
extern u8                   D_801F30E8;
extern u8                   D_801F30FC;
extern u8                   D_801F3130;
extern u8                   D_801F318C;
extern u8                   D_801F3210;
extern u8                   D_801F3224;
extern u8                   D_801F323C;
extern u8                   D_801F32C0;
extern u8                   D_801F3340;
extern u8                   D_801F3370;
extern u8                   D_801F33B8;
extern u8                   D_801F342C;
extern u8                   D_801F3444;
extern u8                   D_801F3474;
extern u8                   D_801F34A4;
extern u8                   D_801F34D8;
extern u8                   D_801F34DC;
extern u8                   D_801F34F0;
extern u8                   D_801F3508;
extern u8                   D_801F3524;
extern u8                   D_801F3528;
extern u8                   D_801F3538;
extern u8                   D_801F35B0;
extern u8                   D_801F35E0;
extern u8                   D_801F35E8;
extern u8                   D_801F35F8;
extern u8                   D_801F3608;
extern u8                   D_801F3670;
extern u8                   D_801F367C;
extern u8                   D_801F36C4;
extern u8                   D_801F36D4;
extern u8                   D_801F376C;
extern u8                   D_801F3784;
extern u8                   D_801F379C;
extern u8                   D_801F37AC;
extern u8                   D_801F37B4;
extern u8                   D_801F37B8;
extern u8                   D_801F37C0;
extern u8                   D_801F37C8;
extern u8                   D_801F37E0;
extern u8                   D_801F37F0;
extern u8                   D_801F3830;
extern u8                   D_801F3854;
extern u8                   D_801F38FC;
extern u8                   D_801F3910;
extern u8                   D_801F3988;
extern u8                   D_801F398C;
extern u8                   D_801F39B8;
extern u8                   D_801F3A44;
extern u8                   D_801F3A84;
extern u8                   D_801F3A8C;
extern u8                   D_801F3A90;
extern u8                   D_801F3AA0;
extern u8                   D_801F3ABC;
extern u8                   D_801F3B08;
extern u8                   D_801F3B1C;
extern u8                   D_801F3B34;
extern u8                   D_801F3B38;
extern u8                   D_801F3B58;
extern u8                   D_801F3B60;
extern u8                   D_801F3BB0;
extern u8                   D_801F3BB4;
extern u8                   D_801F3C30;
extern u8                   D_801F3C48;
extern u8                   D_801F3CA8;
extern u8                   D_801F3CB8;
extern u8                   D_801F3D48;
extern u8                   D_801F3DA8;
extern u8                   D_801F3DAC;
extern u8                   D_801F3DBC;
extern u8                   D_801F3DCC;
extern u8                   D_801F3E58;
extern u8                   D_801F3E64;
extern u8                   D_801F3EAC;
extern u8                   D_801F3F70;
extern u8                   D_801F3FC8;
extern u8                   D_801F3FF8;
extern u8                   D_801F40AC;
extern u8                   D_801F40EC;
extern u8                   D_801F4140;
extern u8                   D_801F4144;
extern u8                   D_801F416C;
extern u8                   D_801F418C;
extern u8                   D_801F41D0;
extern u8                   D_801F4298;
extern u8                   D_801F42B0;
extern u8                   D_801F42C4;
extern u8                   D_801F4300;
extern u8                   D_801F43B4;
extern u8                   D_801F4450;
extern u8                   D_801F453C;
extern u8                   D_801F45A0;
extern u8                   D_801F480C;
extern u8                   D_801F48B8;
extern u8                   D_801F48BC;
extern u8                   D_801F491C;
extern u8                   D_801F4944;
extern u8                   D_801F49E8;
extern u8                   D_801F4A28;
extern u8                   D_801F4A44;
extern u8                   D_801F4A68;
extern u8                   D_801F4AB8;
extern u8                   D_801F4BCC;
extern u8                   D_801F4C2C;
extern u8                   D_801F4C98;
extern u8                   D_801F4CB4;
extern u8                   D_801F4D20;
extern u8                   D_801F4D50;
extern u8                   D_801F4D88;
extern u8                   D_801F4E4C;
extern u8                   D_801F4E60;
extern u8                   D_801F4EF0;
extern u8                   D_801F4F18;
extern u8                   D_801F4F50;
extern u8                   D_801F4F80;
extern u8                   D_801F5014;
extern u8                   D_801F50A4;
extern u8                   D_801F50B8;
extern u8                   D_801F5178;
extern u8                   D_801F52B8;
extern u8                   D_801F52F4;
extern u8                   D_801F52F8;
extern u8                   D_801F531C;
extern u8                   D_801F5340;
extern u8                   D_801F53AC;
extern u8                   D_801F548C;
extern u8                   D_801F5594;
extern u8                   D_801F5634;
extern u8                   D_801F5680;
extern u8                   D_801F576C;
extern u8                   D_801F58D0;
extern u8                   D_801F599C;
extern u8                   D_801F5ABC;
extern u8                   D_801F5B84;
extern u8                   D_801F5C50;
extern u8                   D_801F5C90;
extern u8                   D_801F5D20;
extern u8                   D_801F604C;
extern u8                   D_801F60F4;
extern u8                   D_801F62A8;
extern u8                   D_801F62AC;
extern u8                   D_801F6328;
extern u8                   D_801F6374;
extern u8                   D_801F63B4;
extern u8                   D_801F6474;
extern u8                   D_801F64CC;
extern u8                   D_801F6668;
extern u8                   D_801F672C;
extern u8                   D_801F6770;
extern u8                   D_801F6848;
extern u8                   D_801F6870;
extern u8                   D_801F6A20;
extern u8                   D_801F6A68;
extern u8                   D_801F6AD0;
extern const MenuPanelFuncs g_UiPanels;

/* Retail function prototypes (one declaration each). */
s8                                func_8014DE78(void);
extern void                       func_8014FB80(s16 x, s16 y, u16 clut, u8 shade);
void                              func_80150E48(void);
void                              func_80150E98(void);
void                              func_80150F08(void);
void                              func_80150F3C(void);
void                              func_80150F8C(void);
void                              func_8015102C(void);
void                              func_801510DC(void);
void                              func_8015115C(void);
void                              func_801511C8(void);
void                              func_80151334(void);
void                              func_80151480(void);
void                              func_80151538(void);
void                              func_801515F4(void);
void                              func_80151710(void);
void                              func_801517AC(void);
void                              func_80151820(void);
void                              func_80151844(void);
void                              func_80151894(void);
void                              func_80151964(void);
void                              func_80151A98(void);
extern void                       func_80151B08(void);
extern void                       func_80151B50(void);
void                              func_80151D3C(void);
void                              func_80151D8C(void);
void                              func_80151DCC(void);
void                              func_80152370(void);
void                              func_801523D0(void);
void                              func_80152420(void);
void                              func_80152470(void);
void                              func_801524C0(void);
void                              UI_MessageAnswerSet5(void);
void                              UI_MessageAnswerSet6(void);
void                              UI_MessageAnswerSet7(void);
void                              UI_MessageAnswerSet8(void);
void                              UI_MessageAnswerSet9(void);
void                              UI_MessageAnswerSet10(void);
void                              UI_MessageAnswerSet11(void);
void                              UI_MessageAnswerSet12(void);
void                              UI_MessageAnswerSet13(void);
void                              UI_MessageAnswerSet14(void);
void                              UI_MessageAnswerSet15(void);
/* The cell record the tile-ring draw is working on. */
extern s8*                        D_1F800010;
void                              func_8015642C(u8* obj, s32 x, s32 y);
void                              func_8015684C(u32* record, s32 cell_x, s32 cell_y);
void                              func_801569B8(u8* record, s32 cell_x, s32 cell_y);
void                              func_8015763C(void);
void                              func_80157644(u32* record);
void                              func_801576A0(u32* record);
void                              func_801576FC(u8* record);
void                              func_801583BC(void* obj);
void                              func_80158830(void* obj);
void                              func_80158940(void* obj);
extern void                       func_8015A170(void);
extern void                       func_8015A9A4(void);
s8                                func_8015AD00(PanelSortItem* sort_list);
void                              func_8015B2AC(s16* out, s32* in);
s32                               func_8015B83C(u8** cursor);
void                              func_80163698(void);
u8*                               func_801642F4(u8* dst, const u8* src, u32 count);
extern void                       func_80167428(void);
/* func_8016BA04 */
void                              SND_QuitSpu(void);
extern const BundleOpcodeCallback g_BundleRecordOpcodes[]; /* interior of g_BundleOpcodes (index 3); a separate symbol keeps func_801584A4 matching */
extern u8                         D_8017F90D;
s32                               func_801A17A0(u8* entry_record);
void                              func_801D0C04(void);
extern s32                        func_801F2C04(void);

/* Pause or replay the sequence player for the selected sound entry. */
static inline void Snd_ToggleSequencePlayer(void (*action)(short, short), s32 cue_id) {
    if ((cue_id & BYTE_MASK) != 0xFF) {
        action(g_SelectionEffectVoices[g_SelectionSepSlots[(cue_id & BYTE_MASK) * 4]], g_SelectionSequences[(cue_id & BYTE_MASK) * 4]);
    }
}

/* Draw the panel box from the record's position and size words. */
static inline void Slus_DrawPanelBox(void) {
    MenuPanelTask* panel;

    panel = g_UiPanelCurrent;
    UI_WindowDrawPanelBox((s16)panel->pos.x >> 4, (s16)panel->pos.y >> 4, (u8)(panel->u.grow.w >> 4), (u8)(panel->u.grow.h >> 4));
}

s32 SYS_LoadExe(const char* path);

extern u32 g_SndSeReaders[SND_BANK_COUNT];

void SYS_ShowFileNotFound(void);

#endif
