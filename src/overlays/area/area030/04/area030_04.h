#ifndef OVERLAY_WORLD00_FISHING_04_H
#define OVERLAY_WORLD00_FISHING_04_H

/* The world00/area030/04 world overlay's local declarations: the area work table, the
 * route-velocity tables, script state and handlers. Only this image includes
 * the file. */

#include "overlays/area/world00.h"
#include "area/fishing.h"
#include "area/spad.h"
#include "game/item.h"
#include <stdio.h>

#define FISHING_STATE        ((FishingState*)g_Task)
#define FISHING_ROW          ((Actor*)g_CurrentActor)
#define FISHING_ENTRY(index) (&((FishingSceneCue*)g_FishingSpecies)[(index)])

/* The fishing messages: indexes into the message table the pond loads at
 * AREA_MESSAGE_TABLE (the AREA030, AREA089 and AREA129 payload). */
typedef enum FishingMessageId {
    FISHING_MSG_CAUTION          = 60,
    FISHING_MSG_FISH             = 61,
    FISHING_MSG_RETRY            = 62,
    FISHING_MSG_EXIT             = 63,
    FISHING_MSG_QUIT_PROMPT      = 64,
    FISHING_MSG_TOO_MANY_ITEMS   = 65,
    FISHING_MSG_EQUIP_ROD_LURE   = 80,
    FISHING_MSG_EQUIP_ROD        = 81,
    FISHING_MSG_EQUIP_LURE       = 82,
    FISHING_MSG_DATA_TITLE       = 96,
    FISHING_MSG_DATA_PAGE_HINT   = 97,
    FISHING_MSG_HOW_TO_FISH      = 111,
    FISHING_MSG_HOW_TO_PAGE_HINT = 112,
} FishingMessageId;

#define g_CurrentActor            ((u8*)g_CurrentActor)

/* The fish species the pond holds: the fish items from ITEM_JELLYFISH to ITEM_MACKEREL. */
#define FISHING_FISH_SPECIES      (ITEM_MACKEREL - ITEM_JELLYFISH + 1)

/* The pond camera follows the lure between these heights (16.16 cells); a
 * hooked fish out of the water is at FISHING_CATCH_HEIGHT. */
#define FISHING_CAMERA_Y_MIN      TO_COORD(21)
#define FISHING_CAMERA_Y_MAX      TO_COORD(60)
#define FISHING_CATCH_HEIGHT      TO_COORD_HALF(62)

#define FISHING_HEADER_SLIDE_STEP 16
#define FISHING_SHOP_COLUMNS_X    88
#define FISHING_SHOP_COLUMNS_Y    40
#define FISHING_SHOP_SLIDE_STEP   45
#define FISHING_EQUIP_PANEL_X     16
#define FISHING_ITEM_PANEL_X      164
#define FISHING_PANEL_CONTENT_Y   64
#define FISHING_CATCH_BAR_Y       78
#define FISHING_CATCH_ICON_X      128
#define FISHING_CATCH_ICON_Y      91
#define FISHING_CATCH_ICON_STEP   48
#define FISHING_CATCH_RANK_X      176
#define FISHING_CATCH_RANK_Y      156
#define FISHING_CATCH_ROW_Y       148
#define FISHING_CATCH_ROW_STEP    30
#define g_AreaScrollTargetY       (*(u32*)&g_AreaScrollTargetY)

/* The motion word at 0x34 is loaded as a whole, and 0x36 is its upper half. */
typedef union FishingMotion {
    s32 unk_34;

    struct {
        s16 unk_34;
        s16 cursor_36; /* the accessory selection row cursor */
    } half;
} FishingMotion;

/* The bounce accumulator at 0x3C is a word; the key at 0x3E is its upper
 * half, read and written on its own. */
typedef union FishingBounce {
    s32 unk_3C;

    struct {
        u16 unk_3C;
        s16 key_3E;
    } half;
} FishingBounce;

/* The low cell of 0x38 is read as a byte and, by func_801E0044, as a
 * halfword over 0x38-0x39: the low half of the fixed-point y, whose sign bit
 * it keeps. */
typedef union FishingStateSlotLow {
    u8  unk_38; /* the byte at 0x38 */
    s16 pos_low_38;
} FishingStateSlotLow;

typedef struct FishingStateSlot {
    FishingStateSlotLow low_38;
    s16                 slot_3A; /* the accessory slot of the selected row; func_801D8364 */
} FishingStateSlot;

ASSERT_SIZE(FishingStateSlot, 4);

/* The cell at 0x38 is read as a word, as a byte and, at 0x3A, as a halfword
 * of its own.  The word holds the work record's y position in 16.16 fixed
 * point: Fishing_FishAppear writes 0x3E0000 - facing * 0xC0000, Fishing_CastInput
 * writes 0x410000, Fishing_LureFly subtracts 0x4000 and func_801E03F8 calls
 * it pos_y while calling 0x34 pos_x.  The accessory drawer func_801D8364
 * stores the accessory slot of the selected row in the 0x3A halfword. */
typedef union FishingStateY {
    s32              pos_y;
    FishingStateSlot half;
} FishingStateY;

ASSERT_SIZE(FishingStateY, 4);

/* One cue row of D_801E1D58: the 16.16 fixed-point height offset and the
 * per-step delta; four rows, indexed by cue_index_06 (Fishing_LureFly). */
typedef struct FishingCueStep {
    s32 offset_00;
    s32 step_04;
} FishingCueStep;

ASSERT_SIZE(FishingCueStep, 0x08);

/* The item pointer at 0x50 and the message text pointer at 0x54 are stored as
 * words and dereferenced as bytes. */
typedef union FishingItemPointer {
    u8* pointer;
    s32 word;
} FishingItemPointer;

/* One fishing animation step: the animation func_8014D8D4 plays (bit 7 ends
 * the sequence), the next step index and the x/y deltas applied to the rod
 * position. D_801E207D..F are byte views of the following rows of D_801E207C. */
typedef struct FishingAnimationStep {
    s8 anim_id;
    u8 next_step;
    s8 delta_x;
    s8 delta_y;
} FishingAnimationStep;

ASSERT_SIZE(FishingAnimationStep, 0x4);

/* Scratchpad work area behind g_Task; widths follow the retail accesses. */
typedef struct FishingState {
    u8                            flags;
    u8                            handler_index_01;
    u8                            mode_index_02;
    u8                            sub_index_03;
    u8                            flag_04;
    u8                            pad_05[0x1];
    u8                            cue_index_06;
    u8                            counter_07;
    u8                            counter_08;
    u8                            step_timer_09;
    u8                            step_index_0A;
    u8                            saved_index_0B;
    s32                           pos_x_0C;
    s32                           cursor_10; /* the icon cursor; it steps by 8 and stops at 0xAE */
    s32                           step_14;
    u32                           step_delta_18;
    u32                           unk_1C;
    u32                           step_limit_20;
    u8                            active_flags;
    u8                            saved_25; /* a value copied in from the entry table */
    u8                            saved_26; /* a value copied in from the entry table */
    u8                            saved_value_27;
    u8                            saved_value_28;
    u8                            state_29;
    u8                            state_2A;
    u8                            pad_2B[0x1];
    u16                           unk_2C;
    u16                           origin_x_2E; /* the panel's screen origin x */
    u16                           origin_y_30; /* the panel's screen origin y */
    u8                            pad_32[0x2];
    /* 0x34 */ FishingMotion      motion_34;
    /* 0x38 */ FishingStateY      y_38;
    /* 0x3C */ FishingBounce      bounce_3C;
    /* 0x40 */ u32                unk_40;
    u32                           unk_44;
    u8                            counter_48;
    u8                            counter_49;
    u8                            column_4A; /* the table column the row is read from */
    u8                            row_4B;    /* the table row the entry comes from */
    u8                            pad_4C[0x4];
    /* 0x50 */ FishingItemPointer item_50;
    /* 0x54 */ FishingItemPointer text_54;
    u16                           flags_58;
    u16                           unk_5A;
    u8                            unk_5C;
    s8                            tint_5D; /* the first tuning byte; -0x80 is its terminator */
    s8                            tint_5E; /* the second tuning byte */
    s8                            tint_5F; /* the third tuning byte */
    u32                           unk_60;
    u32                           unk_64;
    u32                           unk_68;
    u32                           unk_6C;
} FishingState;

ASSERT_OFFSET(FishingState, y_38, 0x38);
STATIC_ASSERT(FishingState_slot_3A, DECOMP_OFFSETOF(FishingState, y_38.half.slot_3A) == 0x3A);

/* The 0x24-byte fishing scene cue rows at g_FishingSpecies, indexed by the work's
 * cue_index_06 and selected by the g_FishingPromptSets queue table. value_00 is the
 * scene id func_8014DD3C resolves; count_0A limits the spawn facing. The rest
 * is not modelled. */
typedef struct FishingSceneCue {
    u16 value_00;
    u8  pad_02[8];
    u8  count_0A;
    u8  pad_0B[0x19];
} FishingSceneCue;

ASSERT_SIZE(FishingSceneCue, 0x24);
ASSERT_OFFSET(FishingSceneCue, value_00, 0x00);
ASSERT_OFFSET(FishingSceneCue, count_0A, 0x0A);

/* The world panel's selection state word at the head of each 0x98-byte field
 * work row; Fishing_HookedReel latches the pad state here and the byte at +1 is the
 * world mode. The rest of the row is the field work record. */
typedef struct FishingSelectionState {
    s32 state; /* 0x00 */
    u8  pad[0x94];
} FishingSelectionState;

/* One 0x10-byte panel icon row from D_801E2424: the CLUT x and y (unk_00 and
 * unk_04), the quad size and the U/V origin Fishing_DrawSprite copies into a sprite. */
typedef struct PanelIcon {
    s32 unk_00;
    s32 unk_04;
    u16 width;  /* 0x08 */
    u16 height; /* 0x0A */
    u8  u;      /* 0x0C */
    u8  v;      /* 0x0D */
    u8  pad_0E[2];
} PanelIcon;

ASSERT_SIZE(PanelIcon, 0x10);
ASSERT_OFFSET(PanelIcon, width, 0x08);
ASSERT_OFFSET(PanelIcon, height, 0x0A);
ASSERT_OFFSET(PanelIcon, u, 0x0C);
ASSERT_OFFSET(PanelIcon, v, 0x0D);

/* g_FishingLureRow selects a 0x14-byte row from D_801E2720. */
typedef struct FishingTarget {
    s32 unk_00;    /* 0x00 */
    s32 unk_04;    /* 0x04 */
    s32 unk_08;    /* 0x08 */
    u16 unk_0C;    /* 0x0C */
    u8  unk_0E;    /* 0x0E */
    u8  unk_0F;    /* 0x0F */
    u8  unk_10;    /* 0x10 */
    s8  unk_11;    /* 0x11 */
    u8  pad_12[2]; /* 0x12 */
} FishingTarget;

ASSERT_SIZE(FishingTarget, 0x14);
ASSERT_OFFSET(FishingTarget, unk_00, 0x00);
ASSERT_OFFSET(FishingTarget, unk_04, 0x04);
ASSERT_OFFSET(FishingTarget, unk_08, 0x08);
ASSERT_OFFSET(FishingTarget, unk_0C, 0x0C);
ASSERT_OFFSET(FishingTarget, unk_0E, 0x0E);
ASSERT_OFFSET(FishingTarget, unk_0F, 0x0F);
ASSERT_OFFSET(FishingTarget, unk_10, 0x10);
ASSERT_OFFSET(FishingTarget, unk_11, 0x11);
ASSERT_OFFSET(FishingTarget, pad_12, 0x12);

/* One 0xA-byte panel texture cell: the U/V origin, the quad width, the extra V
 * span and the texture page word. The D_801E218C..D_801E2194 tables are
 * indexed by the panel style and read by Fishing_DrawWindowFill. */
typedef struct PanelTexture {
    u16 u;
    u16 v;
    u16 width;
    u16 v_span;
    u16 tpage;
} PanelTexture;

ASSERT_SIZE(PanelTexture, 0xA);

/* One two-byte panel anchor: signed x/y offsets from the column base. */
typedef struct PanelAnchor {
    s8 x;
    s8 y;
} PanelAnchor;

ASSERT_SIZE(PanelAnchor, 2);

typedef struct FishingAnchors {
    PanelAnchor anchor[3];
} FishingAnchors;

ASSERT_SIZE(FishingAnchors, 6);

/* 17 rows of ten companion-overlay index bytes and the two zero bytes that
 * align D_801E31E0. */
typedef struct FishingCompanionCells {
    u8 cells[17][10];
    u8 align[2];
} FishingCompanionCells;

ASSERT_SIZE(FishingCompanionCells, 0xAC);

typedef struct FishingIcon {
    u8 icon;
    u8 offset;
    u8 first;
    u8 second;
} FishingIcon;

typedef struct FishingIconData {
    FishingIcon records[13];
} FishingIconData;

typedef struct FishingThresholdData {
    u16 thresholds[13];
} FishingThresholdData;

extern s16                   D_800396C0;
extern s16                   D_800396FE;
/* D_800F724C */
extern u8                    s_ShopMode;
extern u8                    D_800F724D;
extern u8                    D_800F724E;
extern u8                    D_800F724F;
extern u8                    D_8014403D;
extern u8                    D_8014403E;
extern u8                    D_801440B1;
extern s32                   D_801440BC;
extern s32                   D_801440C8;
extern u8                    D_80144124;
extern u8                    D_80144125;
extern u8                    D_8014412A;
extern u8                    D_8014412B;
extern u16                   D_80144154;
extern u8                    D_80144199;
extern u8                    D_8014419E;
extern u8                    D_8014420D;
extern u8                    D_80144216;
extern s32                   D_8014421C;
extern u8                    D_80144281;
extern u8                    D_80144286;
extern u8                    D_80144287;
extern u8                    D_80144288;
extern u8                    D_8014428B;
extern u16                   D_801442AC;
extern u16                   D_801442BC;
extern u16                   D_801442BE;
extern u8                    D_801454EC[];
extern s32                   D_80145EC4;
extern u8                    D_80145ED9;
extern u8                    D_80145EDA;
extern s32                   D_80145EE0;
extern s32                   D_80145EE4;
extern u16                   D_80145EE8;
extern u16                   D_80145EEA;
extern u8                    D_8014688C;
extern s32                   D_80146892;
extern s32                   D_80146898;
extern FishingSelectionState D_801468A4[];
extern u8                    D_80146918[];
/* D_80181AC0 */
extern Point2DL              g_FacingOffsets[];
extern char                  D_801D0C04[];
extern char                  D_801D0C08[];
extern char                  D_801D0C10[];
extern char                  D_801D0C14[];
extern FishingAnchors        D_801D0C30;
extern char                  D_801D0C38[];
/* D_801D0C3C */
extern FishingIconData       g_FishingRankIcons;
extern FishingThresholdData  D_801D0C70;
extern u8                    D_801D0C8C[];
extern Callback              D_801E1CD4[];
extern Callback              D_801E1CE8[];
extern Callback              D_801E1CF8[];
extern Callback              D_801E1D00[];
extern u8                    D_801E1D0C[];
/* D_801E1D10 */
extern Callback              g_FishingCastGaugeStates[];
/* D_801E1D20 */
extern Callback              g_FishingLureStates[];
extern u8                    D_801E1D38[];
extern u8                    D_801E1D3C[];
extern FishingCueStep        D_801E1D58[];
extern s32                   D_801E1D5C;
extern Callback              D_801E1D78[];
/* D_801E1D80 */
extern Callback              g_FishingReelGaugeStates[];
extern Callback              D_801E1D8C[];
extern u16                   D_801E1DA0[];
extern u8                    D_801E1E78[];
extern u32                   D_801E1E7C[];
extern u8                    D_801E1E80[];
extern u8                    D_801E1F14[];
extern u8                    D_801E1F16[];
/* D_801E1F20 */
extern u8                    g_FishingPromptSets[][4];
/* D_801E1F44 */
extern Callback              g_FishingPromptStates[];
/* D_801E1F78 */
extern Callback              g_FishingDataStates[];
extern Callback              D_801E1FBC[];
extern Callback              D_801E1FD4[];
extern u8                    D_801E1FE8[];
extern u8                    D_801E1FE9[];
extern Callback              D_801E2000[];
extern u8                    D_801E2008[];
extern u8                    D_801E2009[];
extern u8                    D_801E200A[];
extern Callback              D_801E2014[];
extern s8                    D_801E2024[];
extern u8                    D_801E2025[];
extern s8                    D_801E2026[];
extern Callback              D_801E2048[];
extern u8                    D_801E2050;
extern s32                   D_801E2070;
extern Callback              D_801E2074[];
extern FishingAnimationStep  D_801E207C[];
extern Callback              D_801E20C4[];
extern FishingAnimationStep  D_801E20CC[];
extern u16                   D_801E2114[];
extern u16                   D_801E2120[];
extern PanelTexture          D_801E218C[];
extern u8                    D_801E21C0;
extern u8                    D_801E21CC[];
extern s32                   D_801E21D0;
extern u8                    D_801E21D4[];
extern u8                    D_801E21D9[];
/* D_801E21E0 */
extern Callback              g_FishingSceneModes[];
/* D_801E2210 */
extern Callback              g_FishingEntryStates[];
/* D_801E221C */
extern Callback              g_FishingReadyStates[];
/* D_801E2248 */
extern Callback              g_FishingCastStates[];
extern Callback              D_801E2258[];
/* D_801E2268 */
extern Callback              g_FishingHookedStates[];
extern Callback              D_801E22A4[];
extern Callback              D_801E22B0[];
extern Callback              D_801E22BC[];
extern Callback              D_801E22C8[];
extern Callback              D_801E22D0[];
extern Callback              D_801E22E4[];
extern Callback              D_801E22F0[];
extern Callback              D_801E22FC[];
extern Callback              D_801E2304[];
extern void (*g_FishingFishStates[])(void);
extern u8                    D_801E2330[];
extern u8                    D_801E2331[];
extern Callback              D_801E2340[];
extern Callback              D_801E2348[];
extern u16                   D_801E2354[];
extern s32                   D_801E2384[];
extern s32                   D_801E2388[];
extern s32                   D_801E238C[];
extern s32                   D_801E2390[];
extern PanelIcon             D_801E2424[];
extern u8                    D_801E2720[];
extern u8                    D_801E2748[];
extern u8                    D_801E28C4[];
extern u8                    D_801E28D0[];
extern u8                    D_801E28F4[];
extern s8                    D_801E28F8[];
extern u8                    D_801E2AB8[];
/* D_801E2AC8 */
extern u8                    g_FishingSpecies[];
extern u8                    D_801E2ACA[];
extern u8                    D_801E2AD2[];
extern u8                    D_801E2AD3[];
extern u8                    D_801E2AD5[];
extern u8                    D_801E2AD7[];
extern u8                    D_801E2ADA[];
/* D_801E2DF4 */
extern s8                    g_FishingSpawnCounts[];
extern u8                    D_801E3044[30][8];
extern FishingCompanionCells D_801E3134;
extern u8                    D_801E31E0[];
extern u8                    D_801E31E3;
extern u8                    D_801E31E4[];
extern u8                    D_801E31F0;
extern u8                    D_801E31F4;
extern u8                    D_801E31F8;
extern u8                    D_801E31FC;
extern u8                    D_801E3200;
/* D_801E3204 */
extern u8                    g_FishingFullNoticeShown;
/* D_801E3208 */
extern u8                    g_FishingHookedFish;
/* The equipped rod's row. */
/* D_801E320C */
extern FishingRod*           g_FishingRodRow;
/* D_801E3210 */
extern FishingTarget*        g_FishingLureRow;
/* D_801E3214 */
extern u8                    g_FishingNewRecord;

/* func_800F7094 */
s32  Fishing_ShopDrawItemIcon(s32 x, s32 y, s32 item_id, s32 category, u8 selected);
/* func_8014D6DC */
void Actor_BeginScript(s32 script_index, s32 position);
/* func_801650B4 */
bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
void func_801D0C90(void);
void func_801D0CDC(void);
void func_801D0DDC(void);
void func_801D0E40(void);
void func_801D0E9C(void);
void func_801D0F18(void);
void func_801D0F5C(void);
void func_801D10AC(void);
void func_801D11C0(void);
void func_801D12C8(void);
void func_801D130C(void);
void func_801D1434(void);
void func_801D1538(void);
/* func_801D159C */
void Fishing_DrawHud(s16 panel_x, s16 panel_y);
void func_801D1744(s16 panel_x, s16 panel_y, u8 column_shade);
void func_801D1818(s16 sprite_x, s16 sprite_y, u8 icon_index);
/* func_801D18CC */
void Fishing_DrawIcon(s16 sprite_x, s16 sprite_y, u8 icon_index);
/* func_801D195C */
void Fishing_DrawDepthGauge(s16 panel_x, s16 panel_y);
/* func_801D1B54 */
void Fishing_CastGaugeInit(void);
/* func_801D1B88 */
void Fishing_DrawGaugeFill(s16 quad_x, s16 quad_y, s16 quad_width, u8 corner_shade);
/* func_801D1CF0 */
void Fishing_CastGaugeSweep(void);
void func_801D1F38(void);
void func_801D2034(s16 strip_x, s16 strip_y, u8 icon_mode, s32 icon_count);
/* func_801D210C */
void Fishing_LureCast(void);
/* func_801D23F4 */
void Fishing_LureFly(void);
/* func_801D25F0 */
void Fishing_LureSettle(void);
/* func_801D2648 */
void Fishing_LureFloat(void);
/* func_801D28DC */
void Fishing_LureHooked(void);
void func_801D29BC(void);
void func_801D2AE0(void);
/* func_801D2C34 */
void Fishing_DrawFishArrow(s16 x, s16 y, s8 flip, u8 ot_index);
/* func_801D2D74 */
void Fishing_ReelGaugeInit(void);
/* func_801D2DC4 */
void Fishing_ReelGaugeUpdate(void);
/* func_801D3244 */
void Fishing_DrawReelCursor(s16 panel_x, s16 panel_y, u8 panel_width, s8 u_offset, u8 ot_layer, s8 is_enabled);
void func_801D339C(void);
void func_801D34A0(void);
void func_801D3510(void);
void func_801D3574(void);
void func_801D3650(void);
/* func_801D3684 */
void Fishing_PromptSlideIn(void);
void func_801D36F8(void);
void func_801D3824(void);
void func_801D3898(void);
void func_801D3908(void);
/* func_801D3938 */
void Fishing_PromptSlideOut(void);
void func_801D39B8(void);
void func_801D3A54(void);
void func_801D3C74(void);
void func_801D3F40(void);
void func_801D41E4(void);
void func_801D42E4(void);
void func_801D4378(void);
void func_801D4570(void);
void func_801D45F8(void);
void func_801D4680(void);
/* func_801D4884 */
void Fishing_CatchPageNext(void);
void func_801D4984(void);
void func_801D4B60(void);
void func_801D4C84(void);
void func_801D4E70(void);
void func_801D5048(void);
void func_801D52D4(void);
void func_801D5398(void);
void func_801D54F8(void);
void func_801D5574(void);
void func_801D56F4(void);
void func_801D576C(void);
void func_801D57B0(void);
void func_801D5958(void);
void func_801D5A48(void);
void func_801D5B48(void);
void func_801D5B70(void);
void func_801D5C48(void);
void func_801D5C8C(void);
void func_801D5D88(void);
void func_801D6000(void);
void func_801D6044(void);
void func_801D6128(void);
void func_801D6414(void);
void func_801D64E8(void);
void func_801D6554(void);
void func_801D6598(void);
void func_801D6684(void);
void func_801D69E8(void);
void func_801D6A2C(void);
void func_801D6B28(s8 panel_kind);
void func_801D6CB0(void);
void func_801D6EC4(void);
void func_801D6F08(void);
void func_801D6F34(void);
void func_801D72E4(s16 panel_x, s16 panel_y);
void func_801D7784(u16 list_x, u16 list_y);
/* func_801D799C */
void Fishing_DrawWindowFill(s16 x, s16 y, u8 height, u8 style);
void func_801D7B64(void);
void func_801D7C10(s32 x, s32 y, s32 flags);
void func_801D7D68(s16 x, s16 y, u8 column_mode);
void func_801D7EB0(s32 x, s32 y);
void func_801D8248(s16 x, s16 y, u8 height);
void func_801D8364(s16 panel_x, s16 panel_y);
void func_801D88E0(s16 x, s16 y);
void func_801D8D70(u16 x, u16 y);
void func_801D90FC(s32 x, s16 y);
void func_801D934C(s32 x, s32 y, s32 width, s32 height);
/* func_801D9534 */
s32  Fishing_DrawWindowFrame(s16 frame_x, u16 frame_y, s16 frame_width, s16 frame_height, u8 frame_mode);
void func_801D95C4(u16 x, u16 y, u16 w, u16 h, u8 shade);
void func_801D9740(s32 arg0, u8* arg1, s32 arg2, s32 arg3);
/* func_801D9B58 */
void Fishing_EntryRun(void);
/* func_801D9B9C */
void Fishing_EntryBegin(void);
/* func_801D9C4C */
void Fishing_EntryWait(void);
/* func_801D9C9C */
void Fishing_EntryDone(void);
/* func_801D9CF4 */
void Fishing_ReadyRun(void);
/* func_801D9D38 */
void Fishing_ReadyBegin(void);
/* func_801D9E08 */
void Fishing_ReadyWait(void);
/* func_801D9E40 */
void Fishing_ChooseAction(void);
/* func_801D9FE8 */
void Fishing_ReadyPrompt(void);
/* func_801DA058 */
void Fishing_QuitSlideIn(void);
/* func_801DA168 */
void Fishing_QuitInput(void);
/* func_801DA2A0 */
void Fishing_QuitSlideOut(void);
/* func_801DA3F4 */
void Fishing_CautionSlideIn(void);
/* func_801DA498 */
void Fishing_CautionInput(void);
/* func_801DA508 */
void Fishing_CautionSlideOut(void);
/* func_801DA5B4 */
void Fishing_CastRun(void);
void func_801DA5F8(void);
/* func_801DA638 */
void Fishing_CastInput(void);
void func_801DA714(void);
void func_801DA78C(void);
void func_801DA8E8(void);
void func_801DA92C(void);
void func_801DA9DC(void);
void func_801DAE3C(void);
void func_801DAE84(void);
/* func_801DAED4 */
void Fishing_HookedRun(void);
void func_801DAF18(void);
void func_801DAFBC(void);
void func_801DB04C(void);
void func_801DB0AC(void);
/* func_801DB140 */
void Fishing_HookedReel(void);
/* func_801DB554 */
void Fishing_CatchRecord(void);
void func_801DB620(void);
void func_801DB738(void);
void func_801DB808(void);
void func_801DB8F0(void);
void func_801DBA94(void);
/* func_801DBBAC */
void Fishing_CatchPage(void);
void func_801DBD6C(void);
void func_801DBEDC(void);
void func_801DBFC8(void);
void func_801DC0CC(void);
void func_801DC248(void);
void func_801DC474(void);
void func_801DC4B8(void);
void func_801DC514(void);
void func_801DC568(void);
void func_801DC590(void);
void func_801DC5D4(void);
void func_801DC64C(void);
void func_801DC690(void);
void func_801DC708(void);
void func_801DC74C(void);
void func_801DC7EC(void);
void func_801DC838(void);
void func_801DC888(void);
void func_801DC904(void);
void func_801DC93C(void);
void func_801DCC74(void);
void func_801DCCB0(void);
void func_801DCCF4(void);
void func_801DCDB8(void);
void func_801DCFD0(void);
void func_801DD664(void);
void func_801DD7CC(void);
void func_801DD90C(void);
void func_801DD95C(void);
void func_801DD9A0(void);
void func_801DDB74(void);
void func_801DDBC8(void);
void func_801DDC0C(void);
void func_801DDC54(void);
void func_801DDCB8(void);
void func_801DDCF8(void);
void func_801DDD4C(void);
void func_801DDDBC(void);
/* func_801DDE2C */
void Fishing_SelectGear(void);
void func_801DDE94(s8 request);
void func_801DDEEC(void);
s32  func_801DDF7C(u16 request);
void func_801DDFD4(void);
void func_801DE018(void);
/* func_801DE4AC */
void Fishing_UpdateFish(void);
/* func_801DE5EC */
void Fishing_FishAppear(void);
/* func_801DE82C */
void Fishing_FishSwim(void);
void func_801DEBC4(void);
void func_801DECDC(void);
void func_801DF334(void);
void func_801DFFA8(void);
void func_801DFFEC(void);
void func_801E0044(void);
void func_801E00E0(void);
void func_801E0124(void);
void func_801E01DC(void);
void func_801E023C(void);
/* func_801E026C */
void Fishing_FishStaminaAdd(s8 delta);
bool func_801E02D4(u8 current_byte, u8 target_byte);
/* func_801E0394 */
void Fishing_MoveFish(void);
void func_801E03F8(void);
/* func_801E0680 */
bool Fishing_LureInRange(void);
void func_801E084C(void);
void func_801E09B4(void);
void func_801E0A30(void);
/* func_801E0ABC */
s32  Fishing_CatchScore(u8 row_index, u16 value);
/* func_801E0B6C */
s32  Fishing_TotalScore(void);
/* func_801E0ED0 */
void Fishing_DrawCatchBar(s16 panel_x, s16 panel_y);
/* func_801E0F4C */
void Fishing_DrawCatchIcon(s16 sprite_x, s16 sprite_y, u8 icon_index);
void func_801E1004(s32 item, s32 count, s32 column);
/* func_801E1320 */
void Fishing_DrawRank(s16 x, s16 y);
void Fishing_DrawIconRow(s16 cell_x, s16 cell_y, u16 icon_index);
/* func_801E16DC */
void Fishing_DrawDimScreen(void);
/* func_801E1758 */
void Fishing_DrawPromptBox(s32 x, s32 y);
/* func_801E19CC */
void Fishing_DrawCautionBox(s32 x, s32 y);
/* func_801E1C10 */
bool Fishing_FishStacksFull(void);
void func_801E1C7C(void);

/* When the AREA030 state byte is 3, arm the selection cue and advance the
 * sub-state, then run the shared world update. */
static inline void WorldAdvanceFishingSubState(u8 subState) {
    if (D_80144199 == 3) {
        SND_StopSequence(0, 1);
        SND_PlayBGM(0x28, 0x64, 8);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        func_801DDE94(subState);
        FISHING_STATE->sub_index_03 += 1;
    }
    Actor_StepAnimLoop();
}

/* Draw the area030 cue row and its cell; the cell drawer is the overlay's
 * accessory drawer or the default drawer. */
static inline void FishingDrawCue(u8 accessoryCue) {
    FishingState* record;
    s32           mask;

    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        record = FISHING_STATE;
        mask   = BIT(record->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    func_801D88E0(FISHING_EQUIP_PANEL_X, FISHING_PANEL_CONTENT_Y);
    if (accessoryCue) {
        func_801D8364(FISHING_ITEM_PANEL_X, FISHING_PANEL_CONTENT_Y);
    } else {
        func_801D7EB0(FISHING_ITEM_PANEL_X, FISHING_PANEL_CONTENT_Y);
    }
}

#endif
