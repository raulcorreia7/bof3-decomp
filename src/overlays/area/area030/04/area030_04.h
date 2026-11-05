#ifndef OVERLAY_WORLD00_FISHING_04_H
#define OVERLAY_WORLD00_FISHING_04_H

/* The world00/area030/04 world overlay's local declarations: the area work table, the
 * route-velocity tables, script state and handlers. Only this image includes
 * the file. */

#include "overlays/area/world00.h"
#include "work/area_spad.h"
#include <stdio.h>

#define FISHING_STATE        ((FishingState*)g_SpadWork)
#define FISHING_ROW          ((Actor*)g_CurrentActor)
#define FISHING_ENTRY(index) (&((FishingSceneCue*)D_801E2AC8)[(index)])

/* The main-executable text bank at 0x80010000. D_80010000[] is its u16
 * record-offset table; the panel draws pass `0x80010000 + offset` to
 * func_8014F800, which hands it to func_8014F84C as the text record. */
#define FISHING_TEXT_BANK    0x80010000
#define g_CurrentActor       ((u8*)g_CurrentActor)
#define g_AreaScrollTargetY  (*(u32*)&g_AreaScrollTargetY)

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
 * point: func_801DE5EC writes 0x3E0000 - facing * 0xC0000, func_801DA638
 * writes 0x410000, func_801D23F4 subtracts 0x4000 and func_801E03F8 calls
 * it pos_y while calling 0x34 pos_x.  The accessory drawer func_801D8364
 * stores the accessory slot of the selected row in the 0x3A halfword. */
typedef union FishingStateY {
    s32              pos_y;
    FishingStateSlot half;
} FishingStateY;

ASSERT_SIZE(FishingStateY, 4);

/* One cue row of D_801E1D58: the 16.16 fixed-point height offset and the
 * per-step delta; four rows, indexed by cue_index_06 (func_801D23F4). */
typedef struct FishingCueStep {
    s32 offset_00;
    s32 step_04;
} FishingCueStep;

ASSERT_SIZE(FishingCueStep, 0x08);

/* One 10-byte character record row inside the PanelIcon table; D_801E320C is
 * stepped to the selected row by func_801DDE2C. Bytes 0x04 through 0x07 are
 * read as signed (func_801DB140). */
typedef struct FishingCharRow {
    u8 unk_00;    /* 0x00 */
    u8 unk_01;    /* 0x01 */
    u8 unk_02;    /* 0x02 */
    u8 unk_03;    /* 0x03 */
    s8 unk_04;    /* 0x04 */
    s8 unk_05;    /* 0x05 */
    s8 unk_06;    /* 0x06 */
    s8 unk_07;    /* 0x07 */
    u8 pad_08[2]; /* 0x08 */
} FishingCharRow;

ASSERT_SIZE(FishingCharRow, 0x0A);
ASSERT_OFFSET(FishingCharRow, unk_04, 0x04);
ASSERT_OFFSET(FishingCharRow, unk_05, 0x05);
ASSERT_OFFSET(FishingCharRow, unk_06, 0x06);
ASSERT_OFFSET(FishingCharRow, unk_07, 0x07);

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

/* Scratchpad work area behind g_SpadWork; widths follow the retail accesses. */
typedef struct FishingState {
    u8                            flags_00;
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
    u8                            flags_24;
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

/* The 0x24-byte fishing scene cue rows at D_801E2AC8, indexed by the work's
 * cue_index_06 and selected by the D_801E1F20 queue table. value_00 is the
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
 * work row; func_801DB140 latches the pad state here and the byte at +1 is the
 * world mode. The rest of the row is the field work record. */
typedef struct FishingSelectionState {
    s32 state; /* 0x00 */
    u8  pad[0x94];
} FishingSelectionState;

/* One 0x10-byte panel icon row from D_801E2424: the two texture-page words,
 * the quad size and the U/V origin func_801E0DCC copies into a sprite. */
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

/* D_801E3210 selects a 0x14-byte row from D_801E2720. */
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
 * indexed by the panel style and read by func_801D799C. */
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

extern u16                   D_80010000[];
extern u16                   D_80010078;
extern u16                   D_8001007A;
extern u16                   D_8001007C;
extern u16                   D_8001007E;
extern u16                   D_80010080;
extern u16                   D_80010082;
extern u16                   D_800100A0;
extern u16                   D_800100A2;
extern u16                   D_800100A4;
extern u16                   D_800100C0;
extern u16                   D_800100C2;
extern u16                   D_800100DE;
extern u16                   D_800100E0;
extern s16                   D_800396C0;
extern s16                   D_800396FE;
extern u8                    D_800F724C;
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
extern u8                    D_80145026;
extern u8                    D_80145027;
extern u8                    D_80145028;
extern u8                    D_801454EC[];
extern u8                    D_80145EB5;
extern u8                    D_80145EB6;
extern u8                    D_80145EB8;
extern u8                    D_80145EBA;
extern u32                   D_80145EC4;
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
extern u8                    D_801468C6[];
extern u8                    D_80146918[];
/* D_80181AC0 */
extern FacingStep            g_FacingOffsets[];
extern char                  D_801D0C04[];
extern char                  D_801D0C08[];
extern char                  D_801D0C10[];
extern char                  D_801D0C14[];
extern FishingAnchors        D_801D0C30;
extern char                  D_801D0C38[];
extern FishingIconData       D_801D0C3C;
extern FishingThresholdData  D_801D0C70;
extern u8                    D_801D0C8C[];
extern Callback              D_801E1CD4[];
extern Callback              D_801E1CE8[];
extern Callback              D_801E1CF8[];
extern Callback              D_801E1D00[];
extern u8                    D_801E1D0C[];
extern Callback              D_801E1D10[];
extern Callback              D_801E1D20[];
extern u8                    D_801E1D38[];
extern u8                    D_801E1D3C[];
extern FishingCueStep        D_801E1D58[];
extern s32                   D_801E1D5C;
extern Callback              D_801E1D78[];
extern Callback              D_801E1D80[];
extern Callback              D_801E1D8C[];
extern u16                   D_801E1DA0[];
extern u8                    D_801E1E78[];
extern u32                   D_801E1E7C[];
extern u8                    D_801E1E80[];
extern u8                    D_801E1F14[];
extern u8                    D_801E1F16[];
extern u8                    D_801E1F20[][4];
extern Callback              D_801E1F44[];
extern Callback              D_801E1F78[];
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
extern Callback              D_801E21E0[];
extern Callback              D_801E2210[];
extern Callback              D_801E221C[];
extern Callback              D_801E2248[];
extern Callback              D_801E2258[];
extern Callback              D_801E2268[];
extern Callback              D_801E22A4[];
extern Callback              D_801E22B0[];
extern Callback              D_801E22BC[];
extern Callback              D_801E22C8[];
extern Callback              D_801E22D0[];
extern Callback              D_801E22E4[];
extern Callback              D_801E22F0[];
extern Callback              D_801E22FC[];
extern Callback              D_801E2304[];
extern void (*D_801E2314[])(void);
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
extern u8                    D_801E2AC8[];
extern u8                    D_801E2ACA[];
extern u8                    D_801E2AD2[];
extern u8                    D_801E2AD3[];
extern u8                    D_801E2AD5[];
extern u8                    D_801E2AD7[];
extern u8                    D_801E2ADA[];
extern s8                    D_801E2DF4[];
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
extern u8                    D_801E3204;
extern u8                    D_801E3208;
extern FishingCharRow*       D_801E320C;
extern FishingTarget*        D_801E3210;
extern u8                    D_801E3214;

s32  func_800F7094(s32 arg0, s16 arg1, u8 arg2, s32 arg3, s32 arg4);
/* func_8014D6DC */
void Actor_BeginScript(s32 raw_selector, s32 raw_code);
/* func_801650B4 */
bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
s32  func_801BDD58(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record);
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
void func_801D159C(s16 panel_x, s16 panel_y);
void func_801D1744(s16 panel_x, s16 panel_y, u8 column_shade);
void func_801D1818(s16 sprite_x, s16 sprite_y, u8 icon_index);
void func_801D18CC(s16 sprite_x, s16 sprite_y, u8 icon_index);
void func_801D195C(s16 panel_x, s16 panel_y);
void func_801D1B54(void);
void func_801D1B88(s16 quad_x, s16 quad_y, s16 quad_width, u8 corner_shade);
void func_801D1CF0(void);
void func_801D1F38(void);
void func_801D2034(s16 strip_x, s16 strip_y, u8 icon_mode, s32 icon_count);
void func_801D210C(void);
void func_801D23F4(void);
void func_801D25F0(void);
void func_801D2648(void);
void func_801D28DC(void);
void func_801D29BC(void);
void func_801D2AE0(void);
void func_801D2C34(s16 arg0, s16 arg1, s8 arg2, u8 arg3);
void func_801D2D74(void);
void func_801D2DC4(void);
void func_801D3244(s16 panel_x, s16 panel_y, u8 panel_width, s8 u_offset, u8 ot_layer, s8 is_enabled);
void func_801D339C(void);
void func_801D34A0(void);
void func_801D3510(void);
void func_801D3574(void);
void func_801D3650(void);
void func_801D3684(void);
void func_801D36F8(void);
void func_801D3824(void);
void func_801D3898(void);
void func_801D3908(void);
void func_801D3938(void);
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
void func_801D4884(void);
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
void func_801D799C(s16 x, s16 y, u8 height, u8 style);
void func_801D7B64(void);
void func_801D7C10(s32 arg0, s32 arg1, s32 arg2);
void func_801D7D68(s16 x, s16 y, u8 column_mode);
void func_801D7EB0(s32 x, s32 y);
void func_801D8248(s16 x, s16 y, u8 height);
void func_801D8364(s16 panel_x, s16 panel_y);
void func_801D88E0(s16 arg0, s16 arg1);
void func_801D8D70(u16 x, u16 y);
void func_801D90FC(s32 x, s16 y);
void func_801D934C(s32 x, s32 y, s32 width, s32 height);
s32  func_801D9534(s16 frame_x, u16 frame_y, s16 frame_width, s16 frame_height, u8 frame_mode);
void func_801D95C4(u16 x, u16 y, u16 w, u16 h, u8 shade);
void func_801D9740(s32 arg0, u8* arg1, s32 arg2, s32 arg3);
void func_801D9B58(void);
void func_801D9B9C(void);
void func_801D9C4C(void);
void func_801D9C9C(void);
void func_801D9CF4(void);
void func_801D9D38(void);
void func_801D9E08(void);
void func_801D9E40(void);
void func_801D9FE8(void);
void func_801DA058(void);
void func_801DA168(void);
void func_801DA2A0(void);
void func_801DA3F4(void);
void func_801DA498(void);
void func_801DA508(void);
void func_801DA5B4(void);
void func_801DA5F8(void);
void func_801DA638(void);
void func_801DA714(void);
void func_801DA78C(void);
void func_801DA8E8(void);
void func_801DA92C(void);
void func_801DA9DC(void);
void func_801DAE3C(void);
void func_801DAE84(void);
void func_801DAED4(void);
void func_801DAF18(void);
void func_801DAFBC(void);
void func_801DB04C(void);
void func_801DB0AC(void);
void func_801DB140(void);
void func_801DB554(void);
void func_801DB620(void);
void func_801DB738(void);
void func_801DB808(void);
void func_801DB8F0(void);
void func_801DBA94(void);
void func_801DBBAC(void);
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
void func_801DDE2C(void);
void func_801DDE94(s8 request);
void func_801DDEEC(void);
s32  func_801DDF7C(u16 request);
void func_801DDFD4(void);
void func_801DE018(void);
void func_801DE4AC(void);
void func_801DE5EC(void);
void func_801DE82C(void);
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
void func_801E026C(s8 delta);
s32  func_801E02D4(u8 current_byte, u8 target_byte);
void func_801E0394(void);
void func_801E03F8(void);
bool func_801E0680(void);
void func_801E084C(void);
void func_801E09B4(void);
void func_801E0A30(void);
s32  func_801E0ABC(u8 row_index, u16 value);
s32  func_801E0B6C(void);
void func_801E0ED0(s16 panel_x, s16 panel_y);
void func_801E0F4C(s16 sprite_x, s16 sprite_y, u8 icon_index);
void func_801E1004(s32 item, s32 count, s32 column);
void func_801E1320(s16 x, s16 y);
void func_801E162C(s16 cell_x, s16 cell_y, u16 icon_index);
void func_801E16DC(void);
void func_801E1758(s32 x, s32 y);
void func_801E19CC(s32 x, s32 y);
s32  func_801E1C10(void);
void func_801E1C7C(void);

/* When the AREA030 state byte is 3, arm the selection cue and advance the
 * sub-state, then run the shared world update. */
static inline void WorldAdvanceFishingSubState(u8 subState) {
    if (D_80144199 == 3) {
        SND_StopSequence(0, 1);
        SND_PlayBgm(0x28, 0x64, 8);
        SND_PlayCue(EMI_CUE_ID(2, 3));
        func_801DDE94(subState);
        FISHING_STATE->sub_index_03 += 1;
    }
    func_8014D978();
}

/* Draw the area030 cue row and its cell; the cell drawer is the overlay's
 * accessory drawer or the default drawer. */
static inline void FishingDrawCue(u8 accessoryCue) {
    FishingState* record;
    s32           mask;

    func_801D9534(0x14, 0x12, 0x118, 0x13, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        record = FISHING_STATE;
        mask   = BIT(record->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);
    func_801D88E0(0x10, 0x40);
    if (accessoryCue) {
        func_801D8364(0xA4, 0x40);
    } else {
        func_801D7EB0(0xA4, 0x40);
    }
}

#endif
