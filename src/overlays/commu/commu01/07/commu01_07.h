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

extern u8             D_801455C9[];
extern OverlayHeader  D_801D0C00;
/* D_801D4BCC */
extern Callback       g_Commu01States[COMMU01_STEP_COUNT];
/* D_801D4BD8 */
extern Callback       g_Commu01Step2Funcs[COMMU01_STEP2_COUNT];
extern Callback       D_801D4BE4[];
/* D_801D4BEC */
extern Callback       g_Commu01Step2Sub1Funcs[COMMU01_STEP2_SUB1_COUNT];
extern CommuCellFrame D_801D4C44[COMMU_CELL_FRAME_COUNT];
extern u8             D_801D4DF4;
extern u8             D_801D4DF8;
extern u8             D_801D4DFC;
extern u8             D_801D4E00;
extern u8             D_801D4E04;
extern u8             D_801D4E08;
extern u16            D_801D4E0C;
extern u8             D_801D4E10;
extern u16            D_801D4E14;
extern u8             D_801D4E18;
extern u8             D_801D4E1C;
extern u8             D_801D4E20;
extern u8             D_801D4E24;
extern u8             D_801D4E28;
extern u8             D_801D4E2C;
extern u8             D_801D4E30;
extern u8             D_801F286D[];

void func_801D28A4(s32 x, s32 y, s32 fairy_index, s32 selected);
void func_801D3038(void);
void func_801D36FC(s32 cell, s32 selected);
void func_801D3984(s32 x, s32 y, s32 arg2);
u8   func_801D3A48(u8 arg);
u8   func_801D3AA0(s32 job_type, s32 job_number);
void func_801D3B0C(u8* arg0);
void func_801D4694(u16* arg0, s16* arg1, s32 arg2, s32 arg3);
s32  func_801D482C(s32 arg0);
void func_801D49C4(void);
void func_801D4AAC(u8* room);

#endif
