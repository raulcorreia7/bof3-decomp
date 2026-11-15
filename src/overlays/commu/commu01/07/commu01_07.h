#ifndef OVERLAY_ETC_COMMU01_07_H
#define OVERLAY_ETC_COMMU01_07_H

/* The etc/commu01/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* Entries of the handler tables. */
#define COMMU01_STEP_COUNT       3
#define COMMU01_STEP2_COUNT      3
#define COMMU01_STEP2_SUB1_COUNT 6
/* The cell frames the cell outline draws. */
#define COMMU_CELL_FRAME_COUNT   9

/* A cell frame's three screen points, each x then y. */
typedef struct CommuCellFrame {
    u16 points[3][2];
} CommuCellFrame;

ASSERT_OFFSET(CommuCellFrame, points, 0x00);
ASSERT_SIZE(CommuCellFrame, 0xC);

typedef struct CommuSelectionPair {
    u8 count;
    u8 value;
} CommuSelectionPair;

ASSERT_OFFSET(CommuSelectionPair, count, 0x0);
ASSERT_OFFSET(CommuSelectionPair, value, 0x1);
ASSERT_SIZE(CommuSelectionPair, 0x2);

extern u8                 D_801455C9[];
extern s8                 D_801455C2;
extern u16                D_80010000[];
extern u8                 D_801D0C04[12];
extern char               D_801D0C10[];
extern char               D_801D0C14[];
extern u16                D_801D0C18[9];
/* g_EmiOverlayHeader */
extern OverlayHeader      g_EmiOverlayHeader;
extern u16                D_801D4BB8[10];
/* D_801D4BCC */
extern Callback           g_Commu01States[COMMU01_STEP_COUNT];
/* D_801D4BD8 */
extern Callback           g_Commu01Step2Funcs[COMMU01_STEP2_COUNT];
extern Callback           D_801D4BE4[];
/* D_801D4BEC */
extern Callback           g_Commu01Step2Sub1Funcs[COMMU01_STEP2_SUB1_COUNT];
extern u8                 D_801D4C04[12];
extern u16                D_801D4C10[4];
extern CommuSelectionPair D_801D4C18[22];
extern CommuCellFrame     D_801D4C44[COMMU_CELL_FRAME_COUNT];
extern u8                 D_801D4DF4;
extern u8                 D_801D4DF8;
extern u8                 D_801D4DFC;
extern u8                 D_801D4E00;
extern u8                 D_801D4E04;
extern u8                 D_801D4E08;
extern u16                D_801D4E0C;
extern u8                 D_801D4E10;
extern u16                D_801D4E14;
extern u8                 D_801D4E18;
extern u8                 D_801D4E1C;
extern u8                 D_801D4E20;
extern u8                 D_801D4E24;
extern u8                 D_801D4E28;
extern u8                 D_801D4E2C;
extern u8                 D_801D4E30;
extern u8                 D_801F286D[];

/* The column of the selected fairy room in its row of four. */
static inline s32 Commu01_RoomColumn(u8 selection) {
    s32 index;
    s32 offset;

    index  = selection - 1;
    offset = index;
    if (index < 0) {
        offset = selection + 2;
    }
    return index - ((offset >> 2) << 2);
}

void func_801D28A4(s32 x, s32 y, s32 fairy_index, s32 selected);
void func_801D3038(void);
void func_801D36FC(s32 cell, s32 selected);
void func_801D3984(s32 x, s32 y, s32 bright);
u8   func_801D3A48(u8 arg);
u8   func_801D3AA0(u8 type, u8 index);
void func_801D3B0C(u8* arg0);
void func_801D4694(u16* arg0, s16* arg1, s32 arg2, s32 arg3);
s32  func_801D482C(s32 arg0);
void func_801D49C4(void);
void func_801D4AAC(u8* room);

#endif
