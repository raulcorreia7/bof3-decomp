#ifndef SLUS_004_22_H
#define SLUS_004_22_H

/* The main executable's local declarations: the EMI loader, its CD and SPU
 * state, the window state and the data symbols its units share. The shared
 * subsystem headers own the cross-image names; only this executable includes
 * this file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "common/vector.h"
#include "game.h"
#include "sys/cd.h"
#include "sys/exe.h"
#include "sys/gameui.h"
#include "sys/loader_tail.h"
#include "sys/lz77.h"
#include "sys/scene.h"
#include "area/area.h"
#include "area/fishing.h"
#include "area/map.h"
#include "menu/inventory.h"
#include "menu/panel.h"
#include "menu/party.h"
#include "menu/save.h"
#include "slus/facing.h"
#include "slus/part.h"
#include "area/spad.h"
#include "menu/save_data.h"
#include <stdio.h>
#include "common/util.h"
#include <memory.h>

/* Constants. */

/* Fixed retail addresses the units dereference. */
#define SCENE_TABLE_BASE           0x800E3800u          /* scene table: a u32 count, then AreaActorDef entries */
#define RESOURCE_TABLE_BASE        0x8001A000u          /* resource id table. @source: read:Message_GetText@0x801502D0 */
#define RESOURCE_ID_GROUP_WORD(id) (((id) >> 12) & 0xC) /* byte offset of the group base word: id bits 14 and 15 times 4 */
#define RESOURCE_ID_INDEX(id)      ((id) & 0x3FFF)      /* index into the group's u16 offset table */
#define SLUS_LOAD_ADDRESS          0x80010000u          /* the main executable's link address */
#define AREA_CODE_BASE             0x800F5000u          /* the area code base (AreaHandlerRecord.code_base_0C) */
#define WORD_SIGN_BIT              0x80000000u          /* the sign bit of a word */
#define COPY_KERNEL_ENTRY          ((u32) & D_8016432C) /* resume entry of the stream copy kernel */
#define MAP_ZONE_COUNT             666                  /* records in g_AreaEncounterZones */
#define MAP_ZONE_LIST_COUNT        200                  /* lists in g_EncounterZones, one per map index */
#define MAP_ZONE_SIZE              0x08
/* The tone a cue reader looked up last: D_8018B40C is the tone's offset inside
 * the VAB header at `vab_header` (a word of g_SndBankHeaders). */
#define CUE_TONE(vab_header)       ((VagAtr*)(D_8018B40C + (vab_header)))
#define g_SceneRecord              (*(RecordKey*)&g_SceneState)
#define g_CurrentActor             ((u8*)g_CurrentActor)

/* Store the row entry the menu selection picks and latch the delay it selects.
 * Kept: as an inline the row literal folds into `addiu` where retail shifts
 * first (instruction 4 differs in 4 of 4 members); the member also returns from
 * inside. */
#define SLUS_SELECT_ANSWER_MESSAGE(row, delay0, delay1)                               \
    do {                                                                              \
        u16 value;                                                                    \
                                                                                      \
        g_MessageRequest = g_AnswerMessages[(row) + g_MessageWindow.selection_index]; \
        switch (g_MessageWindow.selection_index) {                                    \
            case 0:                                                                   \
                value = (delay0);                                                     \
                break;                                                                \
            case 1:                                                                   \
                value = (delay1);                                                     \
                break;                                                                \
            default:                                                                  \
                return;                                                               \
        }                                                                             \
        g_ScriptVars[0] = (u8)value;                                                  \
    } while (0)

/* Force the word's top byte to the bundle tag and run its bundle-list entry. A
 * bare statement macro: the member declares `word`. The do/while form moves
 * bytes. Kept: as an inline the bundle tag is an argument and the mask
 * loads into $a1 instead of $v1 (2 of 2 members differ). */
#define SLUS_RETAG_BUNDLE_AND_RUN(bundle_tag)                                                         \
    word    = (*record & 0x00FFFFFF) | (bundle_tag);                                                  \
    *record = word;                                                                                   \
    func_801576FC((u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4 + (word & HALF_MASK) * 4)

/* One alias arm of a cue reader: the tone table and the cue table of the bank `alias`. */
#define SLUS_CUE_ALIAS_ARM(alias, tones, cues)   \
    case alias:                                  \
        D_8018B314 = CUE_TONE(tones)->min;       \
        D_8018B320 = CUE_TONE(tones)->shift;     \
        D_8018B32C = CUE_TONE(tones)->pan;       \
        D_8018B324 = CUE_TONE(tones)->vol;       \
        D_8018B328 = CUE_TONE(tones)->vol;       \
        D_8018B318 = (cues)[D_8018B404 * 4 + 3]; \
        break;

/* Bank cue reader: loads cue D_8018B404 of the bank's cue table into voice slot 0 and fills one more slot per layer on the next voices (wrapping at 24). The head is the one body of banks 0 to 6; the alias switch that follows lets another bank supply the tone and voice. */
#define SLUS_READ_BANK_CUE_HEAD(bank, cues, tones)                                                            \
    s32 cue;                                                                                                  \
    s16 program;                                                                                              \
    s16 tone;                                                                                                 \
    s16 voice;                                                                                                \
                                                                                                              \
    D_8018B30C = (bank);                                                                                      \
    cue        = D_8018B404 * 4;                                                                              \
    D_8018B3E0 = (cues)[cue];                                                                                 \
    program    = (cues)[cue + 1] & EMI_CUE_PROGRAM_MASK;                                                      \
    D_8018B308 = program;                                                                                     \
    D_8018B3F4 = (cues)[cue + 1] & EMI_CUE_USE_CUE_VOLUME_FLAG;                                               \
    tone       = (cues)[cue + 2] >> 4;                                                                        \
    D_8018B310 = tone;                                                                                        \
    D_8018B3E8 = (cues)[cue + 2] & EMI_CUE_COMPARE_MASK;                                                      \
    D_8018B40C = g_VabProgramOffsets[program] + VAB_TONE_TABLE + g_VabToneOffsets[tone];                      \
    D_8018B314 = CUE_TONE((tones))->min;                                                                      \
    D_8018B320 = CUE_TONE((tones))->shift;                                                                    \
    D_8018B32C = CUE_TONE((tones))->pan;                                                                      \
    D_8018B324 = CUE_TONE((tones))->vol;                                                                      \
    D_8018B328 = CUE_TONE((tones))->vol;                                                                      \
    voice      = (cues)[cue + 3] & EMI_CUE_VOICE_MASK;                                                        \
    D_8018B318 = voice;                                                                                       \
    D_8018B3E4 = (cues)[cue + 3] & EMI_CUE_LAYER_MASK;                                                        \
    if (D_8018B3E4 != 0) {                                                                                    \
        D_8018B3E4 = D_8018B3E4 >> 5;                                                                         \
        switch (D_8018B3E4) {                                                                                 \
            case 3:                                                                                           \
                D_8018B380 = (cues)[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;                               \
                D_8018B388 = D_8018B310 + D_8018B3E4;                                                         \
                D_8018B38C = D_8018B314;                                                                      \
                D_8018B398 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B380] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B388]; \
                D_8018B39C = CUE_TONE((tones))->vol;                                                          \
                D_8018B3A0 = CUE_TONE((tones))->vol;                                                          \
                D_8018B3A4 = CUE_TONE((tones))->pan;                                                          \
                D_8018B390 = D_8018B318 + 3;                                                                  \
                if (D_8018B390 >= 24) {                                                                       \
                    D_8018B390 = D_8018B318 + 3 - 24;                                                         \
                }                                                                                             \
            case 2:                                                                                           \
                D_8018B358 = (cues)[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;                               \
                D_8018B360 = D_8018B310 + D_8018B3E4;                                                         \
                D_8018B364 = D_8018B314;                                                                      \
                D_8018B370 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B358] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B360]; \
                D_8018B374 = CUE_TONE((tones))->vol;                                                          \
                D_8018B378 = CUE_TONE((tones))->vol;                                                          \
                D_8018B37C = CUE_TONE((tones))->pan;                                                          \
                D_8018B368 = D_8018B318 + 2;                                                                  \
                if (D_8018B368 >= 24) {                                                                       \
                    D_8018B368 = D_8018B318 + 2 - 24;                                                         \
                }                                                                                             \
            case 1:                                                                                           \
                D_8018B330 = (cues)[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;                               \
                D_8018B338 = D_8018B310 + D_8018B3E4;                                                         \
                D_8018B33C = D_8018B314;                                                                      \
                D_8018B348 = D_8018B320;                                                                      \
                D_8018B40C = g_VabProgramOffsets[D_8018B330] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B338]; \
                D_8018B34C = CUE_TONE((tones))->vol;                                                          \
                D_8018B350 = CUE_TONE((tones))->vol;                                                          \
                D_8018B354 = CUE_TONE((tones))->pan;                                                          \
                D_8018B340 = D_8018B318 + 1;                                                                  \
                if (D_8018B340 >= 24) {                                                                       \
                    D_8018B340 = D_8018B318 + 1 - 24;                                                         \
                }                                                                                             \
                break;                                                                                        \
        }                                                                                                     \
    }

/* The cue reader of banks 0, 4, 5 and 6, whose alias banks are 1 to 3. */
#define SLUS_READ_BANK_CUE(bank, cues, tones)                            \
    SLUS_READ_BANK_CUE_HEAD(bank, cues, tones)                           \
    if (D_8018B3E0 != 0) {                                               \
        D_8018B30C = D_8018B3E0 & EMI_CUE_ALIAS_MASK;                    \
        switch (D_8018B30C) {                                            \
            SLUS_CUE_ALIAS_ARM(1, g_SndBankHeaders[1], g_SndBankCues[1]) \
            SLUS_CUE_ALIAS_ARM(2, g_SndBankHeaders[2], g_SndBankCues[2]) \
            SLUS_CUE_ALIAS_ARM(3, g_SndBankHeaders[3], g_SndBankCues[3]) \
        }                                                                \
    }

/* Types. */

/* The text, panel and cue handlers share this state block. */
typedef struct MenuState {
    Point2u text;
    Point2u origin;
    u8      step_id;         /* 0x08 */
    u8      panel_index;     /* 0x09 */
    s8      last_row;        /* 0x0A */
    s8      selection_index; /* 0x0B */
    s16     cue_counter;     /* 0x0C */
    s16     cue_timer;       /* 0x0E */
} MenuState;

ASSERT_SIZE(MenuState, 0x10);
ASSERT_OFFSET(MenuState, text, 0x00);
ASSERT_OFFSET(MenuState, origin, 0x04);
ASSERT_OFFSET(MenuState, step_id, 0x08);
ASSERT_OFFSET(MenuState, panel_index, 0x09);
ASSERT_OFFSET(MenuState, last_row, 0x0A);
ASSERT_OFFSET(MenuState, selection_index, 0x0B);
ASSERT_OFFSET(MenuState, cue_counter, 0x0C);
ASSERT_OFFSET(MenuState, cue_timer, 0x0E);

/* The spill offsets and the 0x40 extent are retail reads: the decoder stores s0-s7 with `sw s0..s7, 0x20..0x3C($t0)` on the context base. */
typedef struct EMIDecodeContext {
    u8* dst;        /* 0x00 decompressed output cursor */
    u32 unk04;      /* 0x04 not referenced by the decoder */
    u8* src;        /* 0x08 input cursor; match source while state is 12 */
    u32 unk0C;      /* 0x0C cleared by the initialiser, never read */
    u32 state;      /* 0x10 resume state, stored as state * 4 (table offset) */
    u32 pending;    /* 0x14 saved control byte or pending run length */
    u8* limit;      /* 0x18 end of the scratchpad input window */
    u8* copy_entry; /* 0x1C copy-kernel resume entry (0x8016432C) */
    u32 spill[8];   /* 0x20-0x3C outer caller s0-s7, reloaded by func_801642CC */
} EMIDecodeContext;

ASSERT_SIZE(EMIDecodeContext, 0x40);
ASSERT_OFFSET(EMIDecodeContext, spill, 0x20);

/* One status sprite cell: the size index selects a width and height row from D_8017F53C. */
typedef struct SpriteCell {
    u8 size; /* 0x00 low nibble indexes D_8017F53C */
    u8 x;    /* 0x01 signed offset; retail reads it as (s8) */
    u8 y;    /* 0x02 signed offset; retail reads it as (s8) */
    u8 u;    /* 0x03 */
    u8 v;    /* 0x04 */
} SpriteCell;

/* The 0xC-byte panel sort rows at 0x80147CFC: func_8015AD00 fills one row per
 * quad, func_8014BC70 walks the list, and func_8014C47C swaps two rows. The
 * list's second row starts at 0x80147D08 and the depth word at 0x80147D0C, so
 * those addresses are interior views of the same rows. */
typedef struct PanelSortItem {
    u8* primitive; /* 0x00 */
    u16 z;         /* 0x04 - largest projected z of the quad; `lh` reads */
    u16 z0;        /* 0x06 - copy of z; bit 15 is the live-row tag */
    u8* work;      /* 0x08 */
} PanelSortItem;

ASSERT_SIZE(PanelSortItem, 0xC);

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
typedef struct SoundSequence {
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
} SoundSequence;

/* Stack snapshots of the fixed dispatch tables the step handlers copy to the frame and index: Message_DispatchState/func_801510DC copy the eight-entry tables at g_MessageStates/D_80149A7C, func_80151538/Message_DispatchChoiceMode the six-entry tables at D_80149A9C/g_MessageChoiceModes, func_8015196C/func_80151A98 build the two-entry tables on the stack, and g_MessageSteps is the sixteen-entry handler table Message_DispatchTableStep copies. */
typedef struct {
    Callback handlers[8];
} Table8;

typedef struct {
    Callback handlers[6];
} Table6;

typedef struct {
    Callback handlers[2];
} Table2;

typedef struct {
    Callback handlers[16];
} HandlerTable;

typedef struct MenuPanelFuncs {
    Callback handlers[9];
} MenuPanelFuncs;

ASSERT_SIZE(MenuPanelFuncs, 0x24);

typedef struct CallbackTable3 {
    void (*entry[3])(void);
} CallbackTable3;

ASSERT_SIZE(CallbackTable3, 0x0C);

typedef struct CallbackTable5 {
    void (*entry[5])(void);
} CallbackTable5;

ASSERT_SIZE(CallbackTable5, 0x14);

typedef struct SystemDispatchFuncs {
    u32 handlers[6];
} SystemDispatchFuncs;

ASSERT_SIZE(SystemDispatchFuncs, 0x18);

typedef void (*CellFunc)(u8* record, s32 cell_x, s32 cell_y);

/* Record of the D_8017F5B4 table; no field meaning is proven. */
typedef struct {
    u8  unk_00;
    u8  unk_01;
    s16 unk_02;
} Rec_8017F5B4;

ASSERT_SIZE(Rec_8017F5B4, 0x04);

/* Row of the D_8017F960 panel table: tile column offset, tile row offset and
 * the row step multiplied by the panel index; read through the interior symbols
 * D_8017F962 and D_8017F964 by func_8015A098 and func_8015A1D8. */
typedef struct {
    s16 col_offset;
    s16 row_offset;
    s16 scale;
} WindowTextRow;

ASSERT_SIZE(WindowTextRow, 0x06);

/* A tile rectangle of a map and what the field code reads once the party stands in it.
 * func_801A0490 and func_801B3C3C compare the four corners as unsigned bytes against (x, y);
 * `rate` indexes the D_801CD1B8 pair table (Area_RollEncounterThreshold), `kind` is returned by func_801A0348, and
 * func_801A0380 uses `seed` directly when `pick` is 0, else `seed` indexes the D_80181E40 picker. */
typedef struct {
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
    u8 rate;
    u8 kind;
    u8 seed;
    u8 pick;
} EncounterZone;

ASSERT_SIZE(EncounterZone, MAP_ZONE_SIZE);

/* The bank records at g_EmiBanks seen from its second symbol, 0x80146780 (EMIBank + 4):
 * EMI_LoadVabHeader and SND_SetBankLayout reach it through this symbol and a typed
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
 * next row's +0. func_8015A1D8 indexes it by the selection byte. */
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

typedef s8 (*GameFunc)(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);

struct Vec3W {
    s32 w0;
    s32 w1;
    s32 w2;
};

/* Data. */

/* Retail data D_80180000-D_801DFFFF and scratchpad (one declaration each). */
extern u8               D_1F800004;
extern u32              D_1F80000C;
extern SVECTOR          D_1F800014[];
extern u8               D_8000005A;
extern u8               D_80000307;
extern u8               D_800013B5;
/* Retail data below D_80145000 (one declaration each). */
extern s32              D_80010004;
extern EMIDecodeContext D_800327A0[];
extern u8               D_800E3800;

extern u16                         g_AreaCellGrid[AREA_CELL_GRID_ROWS][AREA_CELL_GRID_COLS];
extern u8                          D_80142CC0[];
extern u8                          D_80142CE0[];
extern u32                         D_80143740[];
/* SLUS-only state: overlays declare these addresses with their own views, so
 * the registry does not emit them. */
extern Thread                      D_80143B40[]; /* four slots, 0x80 bytes each */
extern u8                          D_80143D75;
extern u8                          D_80143D76;
extern u8                          D_80143D77;
extern u_long                      D_80143DB8;
extern u8                          D_80143E05;
extern u8                          D_80143E06;
extern u8                          D_80143E07;
extern u32                         D_80143E70[];
extern s32                         D_80143E8C;
extern u32                         D_80143EA0;
extern u32                         D_80143EA4;
extern u8                          D_80143F48[];
extern s16                         g_ScrollHeight[]; /* low half (+2) of the big-endian 0x80143F84 scroll word */
extern volatile u8                 g_SndMono;
extern s32                         D_80144967;
/* Retail data D_80145000-D_80146FFF (one declaration each). */
extern s32                         D_80145030;
extern u8                          D_80145990[];
extern u32*                        D_801459D0[];
extern void*                       D_801459F8;
extern u32                         D_801459FC;
extern u16                         D_80145A54[];
extern u16                         D_80145AA6;
extern u16                         D_80145AAE;
/* Pad repeat decoder state words; shop also reads them (func_801D5D98). */
/* Text cursor cells: the draw-text entry seeds them and the line printer
 * computes with them. */
extern u16                         D_80145ACA;
extern u16                         D_80145ACC;
extern s32                         D_80145DA0;
extern u8                          D_80145E9B[];
extern s32                         D_80145EC4;
extern u8                          D_80145F03;
extern u8                          D_8014626C[];
extern volatile u32                g_EmiPayloadSector;
extern volatile u32                g_EmiBytesLeft;
extern volatile u32                g_EmiLoadArg;
extern volatile u32                g_EmiFirstWord;
extern volatile u16                g_EmiEntryType;
extern volatile u32                g_EmiRingBase;
extern u32                         g_EmiStep;
extern s32                         D_80146474;
extern volatile u32                D_80146478;
extern volatile u8                 g_EmiReadStatus;
extern volatile u8                 g_EmiNextSlot;
extern u8                          D_80146482;
extern u8                          D_80146483;
extern volatile u8                 D_80146484;
extern volatile u8                 D_80146485;
extern volatile u8                 D_80146486;
extern s8                          D_80146488;
extern s8                          g_EmiRingSlot;
extern s8                          D_8014648A;
extern s8                          D_8014648B;
extern s32                         D_8014648C;
extern u16                         g_EmiStreamIdleFrames;
extern u16                         D_80146492;
extern u8                          g_EmiStreamState;
extern u8                          D_80146498[];
extern volatile u8                 g_EmiRingStates[];
extern s32                         D_80146518[];
extern u32                         g_EmiSlotSectors[];
extern EMIBank                     g_EmiBanks[7];
extern volatile EMIAudioLink       D_80146780[];
/* FAKE: SND_SetBankLayout stores the bank records, headers and cue tables through their own symbols;
 * the g_EmiBanks, g_SndBankHeaders and g_SndBankCues views share one base register and shrink it. */
extern u8*                         D_80146784;
extern u32                         D_80146788[];
extern s16                         D_8014678C;
extern s32                         D_80146790;
extern s32                         D_80146794;
extern u8*                         D_80146798;
extern s32                         D_8014679C;
extern u16                         D_801467A0;
extern s32                         D_801467A4;
extern s32                         D_801467A8;
extern u8*                         D_801467AC;
extern s32                         D_801467B0;
extern u16                         D_801467B4;
extern s32                         D_801467B8;
extern s32                         D_801467BC;
extern u8*                         D_801467C0;
extern s32                         D_801467C4;
extern u16                         D_801467C8;
extern s32                         D_801467CC;
extern s32                         D_801467D0;
extern u8*                         D_801467D4;
extern s32                         D_801467D8;
extern u16                         D_801467DC;
extern s32                         D_801467E0;
extern s32                         D_801467E4;
extern u8*                         D_801467E8;
extern s32                         D_801467EC;
extern u16                         D_801467F0;
extern s32                         D_801467F4;
extern s32                         D_801467F8;
extern u8*                         D_801467FC;
extern s32                         D_80146800;
extern u16                         D_80146804;
extern u8                          D_801486A0[];
extern u8                          D_8014871C[];
extern u8                          D_80148798[];
extern u8                          D_80148814[];
extern u8                          D_80148890[];
extern u8                          D_8014890C[];
extern u8                          D_80148988[];
extern s32                         D_80148A18;
extern s32                         D_80148A1C;
extern s32                         D_80148A20;
extern s32                         D_80148A24;
extern s32                         D_80148A28;
extern s32                         D_80148A2C;
extern s32                         D_80148A30;
extern s32                         D_80148A34;
extern s32                         D_80148A38;
extern s32                         D_80148A3C;
extern s32                         D_80148A40;
extern s32                         D_80148A44;
extern s32                         D_80148A48;
extern s32                         D_80148A4C;
extern volatile u32                g_EmiSectorCursor;
extern s32                         D_8014680C;
extern s32                         D_80146810;
extern s32                         D_80146814;
extern s16                         D_80146818;
extern u16                         D_8014681A;
extern u16                         D_8014681C;
extern u16                         D_8014681E;
extern u16                         D_80146820;
extern u8                          D_80146824[];
extern s8                          D_8014682C;
extern s8                          D_8014682E;
extern s8                          D_8014682F;
extern u8                          g_SndCDVolume;
extern s8                          D_80146832;
extern u8                          D_80146834;
extern u8                          D_80146835;
extern CdlATV                      g_SndCDMix;
extern u8                          g_EmiServiceMode;
extern OverlaySlotCursor           D_80146844;
extern u32*                        D_80146848;
extern s16                         D_8014684E;
extern s16                         D_80146850[];
extern s16                         D_80146852;
extern u8                          D_80146855;
extern u8                          D_80146856;
extern volatile u32                D_80146858;
extern volatile u32                D_8014685C;
/* Retail data D_80147000-D_8014FFFF (one declaration each). */
extern u8                          D_80147A58[];
extern u8                          D_80147ACC[];
extern PanelSortItem               D_80147CFC[];
extern PanelSortItem               D_80147D08[]; /* == &D_80147CFC[1] */
extern PanelSortDepth              D_80147D0C[]; /* == &D_80147CFC[1].depth */
extern MATRIX                      D_801481B8;
extern CameraAngle                 D_801481D8;
extern u16                         D_801481E0;
extern s32                         D_801481F0;
extern s32                         D_801481F4;
extern s32                         D_80148200;
extern u8                          D_8014820C;
/* The work-record table: func_8014D4E0 appends g_Task, func_8014BB20 sorts it by the s16 at +0x3E. */
extern Actor*                      D_80148214[];
extern s32                         D_8014828C[];
extern u8                          D_80148331[];
extern u8                          D_80148332[];
extern u8                          D_8014865B;
extern u8                          g_SndBankCues[7][124];
extern u16                         D_80148A04;
extern u16                         D_80148A06;
extern u16                         D_80148A0C;
extern u16                         D_80148A0E;
extern s32                         g_SndBankHeaders[7];
extern s32                         g_SndBankSequences[7];
extern u16                         D_80149010[];
extern u16                         D_80149040[];
extern u16                         D_80149070[];
/* D_801490A3 */
extern u8                          g_MessageChoiceStep;
/* D_801490AC */
extern u32                         g_MessageScript;
extern u8*                         D_801490B0;
extern u8                          D_801490B8[]; /* base form: UI_DrawGlyph takes its address and reads [0] */
extern u8                          D_801490B9;
extern s8                          D_801490BA[];
extern u8                          D_801490BB[];
/* D_801490BC */
extern MenuState                   g_MessageWindow;
extern s16                         D_801490C8; /* cue counter; reads sign at the < 9 test and zero-extends elsewhere */
extern s16                         D_801490CA;
extern u8                          D_801490CE;
extern s32                         D_801490D7;
extern s32                         D_801492E0;
extern s16                         D_801492E2;
extern s16                         D_801492E4;
extern s32                         D_801492FC;
extern s32                         D_80149300;
extern s32                         D_80149304;
extern u16                         D_80149336;
extern u8                          D_8014933D;
/* D_80149340 */
extern u8                          D_80149341;
extern const char                  D_80149990[];
extern const u32                   g_UiLocalModes[];
/* D_80149A5C */
extern const Table8                g_MessageStates;
extern const Table8                D_80149A7C;
extern const Table6                D_80149A9C;
/* D_80149AB4 */
extern const Table6                g_MessageChoiceModes;
/* The 16-entry handler table (code addresses 0x80152370..0x801526C8, the step
 * handlers that follow Message_DispatchTableStep): the shared step byte's indices at and
 * above 0x80 dispatch through it. */
/* D_80149ACC */
extern const HandlerTable          g_MessageSteps;
extern const struct CallbackTable3 D_80149B30;
extern const struct CallbackTable5 D_80149B3C;
extern const struct CallbackTable5 D_80149B50;
extern const struct CallbackTable5 D_80149B64;
extern const VECTOR                D_80149BF0;
extern const u32                   g_EmiCDSteps[];
extern const SystemDispatchFuncs   g_EmiRingSlotHandlers;
extern const char                  D_80149F9C[];
extern const char                  D_80149FAC[];
extern const u32                   D_8014AAB8[4];
extern u8                          D_8016432C;
extern const char                  D_8017F44C[];
extern const void* const           D_8017F470[];
/* Retail data D_80170000-D_8017FFFF (one declaration each). */
extern const u16                   D_8017F56C[10];
extern const Rec_8017F5B4          D_8017F5B4[27];
/* D_8017F628 */
extern const u16                   g_AnswerMessages[32];
extern const CellFunc              D_8017F668[77];
extern const s16                   D_8017F7A8[54];
extern const s16                   D_8017F814[54];
extern const u16                   D_8017F880[10];
extern const u32                   D_8017F8E0[4];
extern void                        func_8014BC70(void);
/* D_8017F8F0 */
extern const ObjectFunc            g_BundleOpcodes[7];
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
extern const SceneFlagPair         D_80181484[SCENE_FLAG_COUNT];
extern const ScriptRef             D_80181BDC[40];
extern const ScriptRef* const      D_80181C7C[11];
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
extern u16                         D_80182288[4];
extern u16                         D_80182290[12];
extern u16                         D_801822AA;
extern u16                         D_801822CA;
extern u16                         D_801822EA;
extern u16                         D_80182308[16];
extern s8                          D_8018232A;
/* D_80182348 */
extern u32                         g_SndBankSpuAddress[3][7];
/* D_8018239C */
extern u32                         g_SndBankHeaderSize[3][7];
/* D_801823F0 */
extern u32                         g_SndBankSequenceSize[3][7];
extern DiscLba                     g_EmiSlotLbas[];
/* D_80183230 */
extern u32                         g_XaStreamSlots[3];
/* D_8018323C */
extern u32                         g_XaCues[3];
extern u32                         g_EmiEntryTypes[11];
extern u32                         g_XaStates[55];
extern u32                         D_80183A1C[17];
extern u32                         D_80183A60[4];
extern u16                         D_80183A70[];
extern u8                          D_8018B2F4;
extern s16                         D_8018B308;
extern s16                         D_8018B30C;
extern s16                         D_8018B310;
extern s16                         D_8018B314;
extern s16                         D_8018B318;
/* The four front-end selection voice slots sit in one 0x28-byte-strided block
 * (D_8018B308 + 0x28 * k, k = 0-3); +0x14 of a slot holds the voice number its
 * cue keys on, which is what the four symbols below name. The state word
 * func_8015D71C fills packs only that number's low byte, so the packing reads
 * take the halfword's low byte. */
extern s16                         D_8018B31C;
extern s16                         D_8018B320;
extern s16                         D_8018B324;
extern s16                         D_8018B328;
extern s16                         D_8018B32C;
extern s16                         D_8018B330;
extern s16                         D_8018B338;
extern s16                         D_8018B33C;
extern s16                         D_8018B340;
extern s16                         D_8018B344;
extern s16                         D_8018B348;
extern s16                         D_8018B34C;
extern s16                         D_8018B350;
extern s16                         D_8018B354;
extern s16                         D_8018B358;
extern s16                         D_8018B360;
extern s16                         D_8018B364;
extern s16                         D_8018B368;
extern s16                         D_8018B36C;
extern s16                         D_8018B370;
extern s16                         D_8018B374;
extern s16                         D_8018B378;
extern s16                         D_8018B37C;
extern s16                         D_8018B380;
extern s16                         D_8018B388;
extern s16                         D_8018B38C;
extern s16                         D_8018B390;
extern s16                         D_8018B394;
extern s16                         D_8018B398;
extern s16                         D_8018B39C;
extern s16                         D_8018B3A0;
extern s16                         D_8018B3A4;
extern s16                         D_8018B3D8;
extern s16                         D_8018B3DC;
extern s16                         D_8018B3E0;
extern s16                         D_8018B3E4;
extern s16                         D_8018B3E8;
extern s16                         D_8018B3EC;
extern s16                         D_8018B3F0;
extern s16                         D_8018B3F4;
extern u16                         D_8018B404;
extern u16                         D_8018B408;
extern u16                         D_8018B40C;
extern s32                         D_8018B410;
extern s32                         D_8018B414;
extern u16                         D_8018B418;
extern u16                         D_8018B41A;
extern SpuVoiceAttr                D_8018B450;
extern s32                         D_8018B454;
extern u16                         D_8018B458;
extern u16                         D_8018B45A;
extern CdlLOC                      D_8018B490;
extern u8                          D_8018B4A0;
extern u8                          D_8018B4A4;
extern u8                          D_8018B4A8;
extern u8                          D_8018B4AC;
extern u32                         D_8018B4B0;
extern void (*D_8018E7D4)(s16 voice);
extern void (*D_8018E988)(s16 voice);
extern s8 D_8018E98C;
extern u8 D_801C839C[];
extern u8 D_801C839D[];
extern void (*D_801C83D8[])(u8*);
extern u8*                   D_801C893C[];
extern u8*                   D_801C8950[];
/* The five row tables of choice resources. Each symbol is a byte scalar, so its
 * rows are addressed with the group's byte stride. */
extern u8                    D_801C8972;
extern u8                    D_801C8FE8;
extern u8                    D_801C90E8[];
extern u8                    D_801C90F0;
extern u8                    D_801C98B0[];
extern u8                    D_801C98B6;
extern u8                    D_801C9E88[];
extern u8                    D_801C9E8C;
extern BattleAbilityCategory D_801CA719[];
extern u8                    D_801CA71A[];
/* Ability elements and flags share a 16-bit mask in this image. */
extern u16                   D_801CA71C;
/* The scratchpad work cell. Not volatile: 37 matched SLUS readers keep the
 * pointer in a register across a block (func_8015AD00 at +0xBC), and a volatile
 * cell adds a reload there. A unit that must reload it after a call assigns it
 * to a local at the call boundary. */
extern u8                    D_801EFEFC;
extern u8                    D_801F016C;
extern u8                    D_801F0488;
extern u8                    D_801F0778;
extern u8                    D_801F2C18;
extern u8                    D_801F2C3C;
extern u8                    D_801F2C64;
extern u8                    D_801F2C94;
extern u8                    D_801F2C9C;
extern u8                    D_801F2CA4;
extern u8                    D_801F2CB0;
extern u8                    D_801F2CD0;
extern u8                    D_801F2D10;
extern u8                    D_801F2D20;
extern u8                    D_801F2DCC;
extern u8                    D_801F2DD4;
extern u8                    D_801F2DD8;
extern u8                    D_801F2DE0;
extern u8                    D_801F2E0C;
extern u8                    D_801F2E24;
extern u8                    D_801F2E54;
extern u8                    D_801F2EC4;
extern u8                    D_801F2EC8;
extern u8                    D_801F2F78;
extern u8                    D_801F2F7C;
extern u8                    D_801F2FA0;
extern u8                    D_801F2FFC;
extern u8                    D_801F3048;
extern u8                    D_801F3058;
extern u8                    D_801F30AC;
extern u8                    D_801F30B0;
extern u8                    D_801F30C0;
extern u8                    D_801F30E8;
extern u8                    D_801F30FC;
extern u8                    D_801F3130;
extern u8                    D_801F318C;
extern u8                    D_801F3210;
extern u8                    D_801F3224;
extern u8                    D_801F323C;
extern u8                    D_801F32C0;
extern u8                    D_801F3340;
extern u8                    D_801F3370;
extern u8                    D_801F33B8;
extern u8                    D_801F342C;
extern u8                    D_801F3444;
extern u8                    D_801F3474;
extern u8                    D_801F34A4;
extern u8                    D_801F34D8;
extern u8                    D_801F34DC;
extern u8                    D_801F34F0;
extern u8                    D_801F3508;
extern u8                    D_801F3524;
extern u8                    D_801F3528;
extern u8                    D_801F3538;
extern u8                    D_801F35B0;
extern u8                    D_801F35E0;
extern u8                    D_801F35E8;
extern u8                    D_801F35F8;
extern u8                    D_801F3608;
extern u8                    D_801F3670;
extern u8                    D_801F367C;
extern u8                    D_801F36C4;
extern u8                    D_801F36D4;
extern u8                    D_801F376C;
extern u8                    D_801F3784;
extern u8                    D_801F379C;
extern u8                    D_801F37AC;
extern u8                    D_801F37B4;
extern u8                    D_801F37B8;
extern u8                    D_801F37C0;
extern u8                    D_801F37C8;
extern u8                    D_801F37E0;
extern u8                    D_801F37F0;
extern u8                    D_801F3830;
extern u8                    D_801F3854;
extern u8                    D_801F38FC;
extern u8                    D_801F3910;
extern u8                    D_801F3988;
extern u8                    D_801F398C;
extern u8                    D_801F39B8;
extern u8                    D_801F3A44;
extern u8                    D_801F3A84;
extern u8                    D_801F3A8C;
extern u8                    D_801F3A90;
extern u8                    D_801F3AA0;
extern u8                    D_801F3ABC;
extern u8                    D_801F3B08;
extern u8                    D_801F3B1C;
extern u8                    D_801F3B34;
extern u8                    D_801F3B38;
extern u8                    D_801F3B58;
extern u8                    D_801F3B60;
extern u8                    D_801F3BB0;
extern u8                    D_801F3BB4;
extern u8                    D_801F3C30;
extern u8                    D_801F3C48;
extern u8                    D_801F3CA8;
extern u8                    D_801F3CB8;
extern u8                    D_801F3D48;
extern u8                    D_801F3DA8;
extern u8                    D_801F3DAC;
extern u8                    D_801F3DBC;
extern u8                    D_801F3DCC;
extern u8                    D_801F3E58;
extern u8                    D_801F3E64;
extern u8                    D_801F3EAC;
extern u8                    D_801F3F70;
extern u8                    D_801F3FC8;
extern u8                    D_801F3FF8;
extern u8                    D_801F40AC;
extern u8                    D_801F40EC;
extern u8                    D_801F4140;
extern u8                    D_801F4144;
extern u8                    D_801F416C;
extern u8                    D_801F418C;
extern u8                    D_801F41D0;
extern u8                    D_801F4298;
extern u8                    D_801F42B0;
extern u8                    D_801F42C4;
extern u8                    D_801F4300;
extern u8                    D_801F43B4;
extern u8                    D_801F4450;
extern u8                    D_801F453C;
extern u8                    D_801F45A0;
extern u8                    D_801F480C;
extern u8                    D_801F48B8;
extern u8                    D_801F48BC;
extern u8                    D_801F491C;
extern u8                    D_801F4944;
extern u8                    D_801F49E8;
extern u8                    D_801F4A28;
extern u8                    D_801F4A44;
extern u8                    D_801F4A68;
extern u8                    D_801F4AB8;
extern u8                    D_801F4BCC;
extern u8                    D_801F4C2C;
extern u8                    D_801F4C98;
extern u8                    D_801F4CB4;
extern u8                    D_801F4D20;
extern u8                    D_801F4D50;
extern u8                    D_801F4D88;
extern u8                    D_801F4E4C;
extern u8                    D_801F4E60;
extern u8                    D_801F4EF0;
extern u8                    D_801F4F18;
extern u8                    D_801F4F50;
extern u8                    D_801F4F80;
extern u8                    D_801F5014;
extern u8                    D_801F50A4;
extern u8                    D_801F50B8;
extern u8                    D_801F5178;
extern u8                    D_801F52B8;
extern u8                    D_801F52F4;
extern u8                    D_801F52F8;
extern u8                    D_801F531C;
extern u8                    D_801F5340;
extern u8                    D_801F53AC;
extern u8                    D_801F548C;
extern u8                    D_801F5594;
extern u8                    D_801F5634;
extern u8                    D_801F5680;
extern u8                    D_801F576C;
extern u8                    D_801F58D0;
extern u8                    D_801F599C;
extern u8                    D_801F5ABC;
extern u8                    D_801F5B84;
extern u8                    D_801F5C50;
extern u8                    D_801F5C90;
extern u8                    D_801F5D20;
extern u8                    D_801F604C;
extern u8                    D_801F60F4;
extern u8                    D_801F62A8;
extern u8                    D_801F62AC;
extern u8                    D_801F6328;
extern u8                    D_801F6374;
extern u8                    D_801F63B4;
extern u8                    D_801F6474;
extern u8                    D_801F64CC;
extern u8                    D_801F6668;
extern u8                    D_801F672C;
extern u8                    D_801F6770;
extern u8                    D_801F6848;
extern u8                    D_801F6870;
extern u8                    D_801F6A20;
extern u8                    D_801F6A68;
extern u8                    D_801F6AD0;
extern const MenuPanelFuncs  g_MenuPanels;

void                    func_8014C47C(struct Vec3W* a, struct Vec3W* b);
extern void             Area_DrawSpriteCell(s32 mirror, SpriteCell* cell, u16 clut);
extern void             Actor_BeginScript(s32 script_index, s32 position);
/* func_8014DB98 */
extern void             Actor_StageAnimStep(void);
/* Retail function prototypes (one declaration each). */
s8                      func_8014DE78(void);
extern void             GFX_ExpandRgb555(u32* pixels, RECT rect);
extern void             GFX_DecodeLzss(u32* packed, RECT rect);
/* func_8014EDF0 */
void                    GFX_FadeToBlack(void);
/* func_8014EE18 */
void                    GFX_FadeFromBlack(void);
/* func_8014EE40 */
void                    GFX_FadeToBlackFast(void);
/* func_8014EE68 */
void                    GFX_FadeFromBlackFast(void);
/* func_8014EE90 */
void                    GFX_FadeToBlackSlow(void);
/* func_8014EEB8 */
void                    GFX_FadeFromBlackSlow(void);
void                    func_8014EEE0(void);
void                    func_8014EF08(void);
/* func_8014EF30 */
void                    GFX_FadeToWhite(void);
/* func_8014EF58 */
void                    GFX_FadeFromWhite(void);
void                    func_8014EF80(void);
void                    func_8014F024(void);
void                    func_8014F16C(void);
/* func_8014F1AC */
void                    GFX_FadeToBlackSlower(void);
/* func_8014F1D4 */
void                    GFX_FadeFromBlackSlower(void);
/* func_8014F1FC */
void                    GFX_FadeToWhiteSlower(void);
/* func_8014F224 */
void                    GFX_FadeFromWhiteSlower(void);
void                    func_8014F24C(void);
void                    func_8014F2F0(void);
/* func_8014F438 */
void                    GFX_FadeToBlackSlowest(void);
void                    func_8014F460(void);
extern void             func_8014FB80(s16 x, s16 y, u16 clut, u8 shade);
/* func_801507BC */
extern void             Message_DispatchState(void);
void                    func_8015083C(void);
void                    func_80150E48(void);
void                    func_80150E98(void);
void                    func_80150F08(void);
void                    func_80150F3C(void);
void                    func_80150F8C(void);
void                    func_8015102C(void);
void                    func_801510DC(void);
void                    func_8015115C(void);
void                    func_801511C8(void);
void                    func_80151334(void);
void                    Message_DispatchAnswerStep(void);
/* func_8015142C */
void                    Message_RestartRequest(void);
void                    func_80151480(void);
void                    Message_StartRequest(void);
void                    func_80151538(void);
void                    func_801515F4(void);
void                    func_80151710(void);
void                    func_801517AC(void);
void                    func_80151820(void);
void                    func_80151844(void);
void                    func_80151894(void);
/* func_801518F4 */
void                    Message_DispatchChoiceMode(void);
void                    func_80151964(void);
/* func_801519F8 */
void                    UI_NextChoice(void);
/* func_80151A48 */
void                    UI_PrevChoice(void);
void                    func_80151A98(void);
extern void             func_80151B08(void);
extern void             func_80151B50(void);
void                    func_80151D3C(void);
void                    func_80151D8C(void);
void                    func_80151DCC(void);
void                    UI_DrawGlyph(s32 color, u8* text);
void                    Message_DispatchTableStep(void);
void                    func_80152370(void);
void                    func_801523D0(void);
void                    func_80152420(void);
void                    func_80152470(void);
void                    func_801524C0(void);
void                    Message_SetAnswerMessage5(void);
void                    Message_SetAnswerMessage6(void);
void                    Message_SetAnswerMessage7(void);
void                    Message_SetAnswerMessage8(void);
void                    Message_SetAnswerMessage9(void);
void                    Message_SetAnswerMessage10(void);
void                    Message_SetAnswerMessage11(void);
void                    Message_SetAnswerMessage12(void);
void                    Message_SetAnswerMessage13(void);
void                    Message_SetAnswerMessage14(void);
void                    Message_SetAnswerMessage15(void);
/* func_80152C9C */
void                    Area_LoadCellColumnPrev(void);
/* func_80152D9C */
void                    Area_LoadCellColumnNext(void);
/* func_80152E94 */
void                    Area_LoadCellRowsPrev(void);
/* func_80152FB0 */
void                    Area_LoadCellRowsNext(void);
extern s32              func_801530D0(void);
extern void             func_80153CC4(u32 unused);
extern void             func_80153D34(void);
extern void             Area_GetCell(s32 px, s32 py, AreaCell* out);
extern s32              Area_UploadCell(s32 column, s32 row, POLY_FT4* context, s32 slot);
extern u16              Area_AllocCellPrimRow(void);
extern void             Area_RequestCellRows(AreaCell* entry);
extern void             Area_FreeCellPrimRow(u16 row_id);
void                    Area_DrawPartQuads(ScenePart* parts, s32 shift_x, s32 shift_y);
void                    func_8015642C(u8* obj, s32 x, s32 y);
void                    func_8015684C(u8* record, s32 cell_x, s32 cell_y);
void                    func_801569B8(u8* record, s32 cell_x, s32 cell_y);
void                    Area_DrawPartAnimation(ScenePart* parts, s32 origin_x, s32 origin_y);
void                    func_80156E00(u8* unit, s32 x, s32 y);
void                    Area_DrawGouraudQuads(ScenePart* parts, s32 shift_x, s32 shift_y);
void                    func_8015763C(void);
void                    func_80157644(u32* record);
void                    func_801576A0(u32* record);
void                    func_801576FC(u8* record);
void                    func_80157CE4(u8* record, s32 cell_x, s32 cell_y);
void                    func_801583BC(void* obj);
void                    func_80158830(void* obj);
void                    func_80158940(void* obj);
void                    func_80158F80(void);
void                    func_80158FE0(void);
void                    func_80159050(void);
void                    func_8015920C(void);
void                    func_80159510(void);
void                    func_80159580(void);
void                    Menu_ClosePanel(void);
void                    func_801598F4(void);
void                    func_80159964(void);
void                    func_8015999C(void);
void                    func_80159A00(void);
void                    func_80159A20(void);
void                    func_80159A90(void);
void                    func_80159B38(void);
extern void             func_80159B9C(s32 x, s32 y, u16 w, u16 h);
void                    func_80159FA0(s32 x, s32 y, u8 width, u8 height);
extern void             func_8015A098(void);
extern void             func_8015A170(void);
extern void             func_8015A1D8(void);
extern void             func_8015A264(void);
/* func_8015A2B0 */
void                    UI_DrawLine(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u8 gray);
extern u8*              UI_DrawTextAt(s32 x, s32 y, u8* text);
void                    func_8015A554(void);
extern void             func_8015A9A4(void);
s8                      func_8015AD00(PanelSortItem* sort_list);
void                    func_8015B2AC(s16* out, s32* in);
s32                     Game_IsScenarioEqual(u8** cursor);
s32                     Game_IsAreaEqual(u8** cursor);
s32                     Game_TestSceneFlag(u8** cursor);
s32                     func_8015B6A8(u8** cursor);
s32                     func_8015B6D0(u8** cursor);
s32                     func_8015B6F8(u8** cursor);
s32                     func_8015B73C(u8** cursor);
s32                     Game_TestEventFlag(u8** cursor);
s32                     Game_HasVitalItem(u8** cursor);
s32                     Game_IsScenarioAtLeast(u8** cursor);
s32                     func_8015B7F0(u8** cursor);
s32                     func_8015B83C(u8** cursor);
s32                     Game_IsScriptVar0Equal(u8** cursor);
s32                     Game_IsScriptVar1Equal(u8** cursor);
s32                     Game_IsScriptVar2Equal(u8** cursor);
s32                     Game_IsScriptVar3Equal(u8** cursor);
s32                     Game_SetScriptVar(u8* operand);
s32                     Game_IsScriptVarEqual(u8* record);
s32                     Game_IncScriptVar(u8* operand);
s32                     func_8015BABC(void);
/* func_8015E994 */
void                    SND_ReadCueBank0(void);
/* func_8015EFAC */
void                    SND_ReadCueBank1(void);
/* func_8015F5C8 */
void                    SND_ReadCueBank2(void);
/* func_8015FBE4 */
void                    SND_ReadCueBank3(void);
/* func_80160200 */
void                    SND_ReadCueBank4(void);
/* func_8016081C */
void                    SND_ReadCueBank5(void);
/* func_80160E38 */
void                    SND_ReadCueBank6(void);
extern void             func_80161454(u32 index);
void                    func_80163230(void);
void                    func_80163698(void);
u8*                     func_801642F4(u8* dst, const u8* src, u32 count);
void                    Char_ApplyMaster(u8* arg);
extern s16              Char_AddStat(u16* value, s16 delta);
/* Retail calls this executable makes into its own units and the overlays. */
void                    Char_ApplyWeapon(void* character);
void                    Char_ApplyArmor(void* character);
void                    Char_ApplyAccessories(void* param);
void                    EMI_LoadPartyCode(u8 member_a, u8 member_b, u8 member_c);
void                    EMI_LoadParty(u8 member_a, u8 member_b, u8 member_c, u8 family);
u8                      EMI_FindPartyArchive(u8 member_a, u8 member_b, u8 member_c);
extern void             func_80167428(void);
/* func_8016BA04 */
void                    SND_QuitSpu(void);
extern const ObjectFunc g_BundleRecordOpcodes[]; /* interior of g_BundleOpcodes (index 3); a separate symbol keeps func_801584A4 matching */
extern u8               D_8017F90D;
void                    func_801A17A0(u8* entry_record);
/* func_801C1254 */
void                    Party_LoadMemberSprite(s32 character_id, s32 party_slot, s32 ignored);
void                    func_801D0C04(void);
extern s32              func_801F2C04(void);

/* Pause or replay the sequence player for the selected sound entry. */
static inline void Snd_ToggleSequencePlayer(void (*action)(short, short), s32 cue_id) {
    if ((cue_id & BYTE_MASK) != 0xFF) {
        action(g_SelectionEffectVoices[g_SelectionCues[(cue_id & BYTE_MASK) * 4]], g_SelectionSequences[(cue_id & BYTE_MASK) * 4]);
    }
}

/* Draw the panel box from the record's position and size words. */
static inline void Slus_DrawPanelBox(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    func_80159B9C((s16)panel->pos.x >> 4, (s16)panel->pos.y >> 4, (u8)(panel->u.grow.width >> 4), (u8)(panel->u.grow.height >> 4));
}

void SYS_Main(void);

void SYS_InitRuntime(void);

void SYS_InitHardware(void);

void SYS_InitDisplay(void);

void SYS_ResetDisplayFrame(u8* work);

void Actor_ReadValue(void);

s32 SYS_LoadExec(const char* path);

void GFX_UploadPalette(void);

void UI_DispatchLocalMode(void);

void GFX_RunBlackFade(s32 delta, s32 semi_trans, s32 order);

void GFX_RunWhiteFade(s32 delta, s32 semi_trans, s32 order);

void func_80154438(void);

void SND_UpdateVoiceStatus(void);

void EMI_ReadToc(void);

void EMI_LoadToRam(void);

void EMI_LoadCompressed(void);

void EMI_LoadToVram(void);

void EMI_LoadVabHeader(void);

void EMI_LoadVabBody(void);

void EMI_LoadSoundCues(void);

void EMI_LoadSequence(void);

s32 EMI_NextEntry(u8 slot);

extern u32 g_SndCueReaders[7];

void EMI_Update(void);

s32 Char_AddResistance(u8* counter, s32 delta);

void SYS_ShowFileNotFound(void);

#endif
