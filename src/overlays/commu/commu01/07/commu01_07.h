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

/* A commu kind's entry rows: the name run its first row reads and how many rows it has. */
typedef struct CommuTypeRows {
    u8 first;
    u8 count;
} CommuTypeRows;

ASSERT_OFFSET(CommuTypeRows, first, 0x0);
ASSERT_OFFSET(CommuTypeRows, count, 0x1);
ASSERT_SIZE(CommuTypeRows, 0x2);

extern u8             D_801455C9[];
extern s8             D_801455C2;
extern u16            D_80010000[];
extern u8             D_801D0C04[12];
extern char           D_801D0C10[];
extern char           D_801D0C14[];
extern u16            D_801D0C18[9];
extern u16            D_801D4BB0[];
/* g_EmiOverlayHeader */
extern u16            D_801D4BB8[10];
/* D_801D4BCC */
extern Callback       g_Commu01States[COMMU01_STEP_COUNT];
/* D_801D4BD8 */
extern Callback       g_Commu01Step2Funcs[COMMU01_STEP2_COUNT];
extern Callback       D_801D4BE4[];
/* D_801D4BEC */
extern Callback       g_Commu01Step2Sub1Funcs[COMMU01_STEP2_SUB1_COUNT];
extern u8             D_801D4C04[12];
extern u16            D_801D4C10[4];
extern u8             D_801D4C18[12][2];
/* The channel each commu record kind blinks. */
extern u8             D_801D4C20[];
extern CommuCellFrame D_801D4C44[COMMU_CELL_FRAME_COUNT];
extern u8             D_801D4CD4[];
extern u8             D_801D4CE0[];
extern u8             D_801D4D34[];
/* The commu request slot run's byte columns: the kind grid line, the cursor box
 * row and the byte the commit clears, each at the run's eight-byte row stride. */
extern u8             D_801457A9[][8];
extern u8             D_801457AA[][8];
extern u8             D_801457AB[][8];
extern CommuTypeRows  D_801D4DD4[];
extern u16            D_801D4DDA[];
extern Point2u        D_801D4DDC[];
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

/* The battle counter that follows the scene event's selection byte; retail loads
 * it off the selection pointer the commu request walks. */
#define COMMU_REQUEST_ANCHOR(rec) (*(u32*)((rec) + 0x73F))

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

void func_801D28A4(s16 x, s16 y, u8 slot, s32 selected);
void func_801D2D98(s16 x, s16 y, s32 width, u8 channel, u8 blink);
void func_801D3038(void);
void func_801D36FC(s32 cell, s32 selected);
void func_801D3984(s32 x, s32 y, s32 bright);
u8   Fairy_GetJobActive(u8 arg);
u8   func_801D3AA0(u8 type, u8 index);
void func_801D3B0C(u8* row);
void func_801D3EFC(s16 x, s16 y, u8 ordinal);
void func_801D4030(s16 x, s16 y, u8 piece);
void func_801D4178(s16 x, s16 y, u8 mode);
s16  func_801D44E0(s16 x, s16 y, u8 kind, u8 mode);
void func_801D4694(s16* out_x, s16* out_y, s32 kind, s32 ordinal);
void func_801D47C4(void);
s32  func_801D482C(s32 ordinal_offset);
void func_801D49C4(void);
void func_801D4AAC(u8* room);
void func_801D4B58(void);

#endif
