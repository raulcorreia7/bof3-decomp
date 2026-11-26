#ifndef OVERLAY_ETC_COMMU01_07_H
#define OVERLAY_ETC_COMMU01_07_H

/* The etc/commu01/07 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

/* Entries of the handler tables. */
#define COMMU01_STEP_COUNT       3
#define COMMU01_STEP2_COUNT      3
#define COMMU01_STEP2_SUB1_COUNT 6

/* Where the cell cursor stands: on the idle fairies, in the room grid or on the job types. */
enum {
    FAIRY_CURSOR_IDLE,
    FAIRY_CURSOR_ROOMS,
    FAIRY_CURSOR_JOBS,
};

/* The cell frames the cell outline draws. */
#define COMMU_CELL_FRAME_COUNT 9

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

/* A piece of the fairy screens: the texture position and size, then the palette column and row. */
typedef struct FairyPiece {
    u8 u;
    u8 v;
    u8 w;
    u8 h;
    u8 clut_x;
    u8 clut_y;
} FairyPiece;

ASSERT_SIZE(FairyPiece, 0x6);

/* The caption rows of g_FairyMenuText the room type list takes before the option lists. */
#define FAIRY_TYPE_LIST_ROWS 10

/* A commu type's entry rows: the name run its first row reads and how many rows it has. */
typedef struct CommuTypeRows {
    u8 first;
    u8 count;
} CommuTypeRows;

ASSERT_OFFSET(CommuTypeRows, first, 0x0);
ASSERT_OFFSET(CommuTypeRows, count, 0x1);
ASSERT_SIZE(CommuTypeRows, 0x2);

extern u16            D_80010000[];
extern s8             D_801455C2;
extern u8             D_801455C4;
extern u8             D_801455C9[];
/* The commu request slot run's byte columns: the type grid line, the cursor box
 * row and the byte the commit clears, each at the run's eight-byte row stride. */
extern u8             D_801457A9[][8];
extern u8             D_801457AA[][8];
extern u8             D_801457AB[][8];
/* D_801D0C04 */
extern u8             g_FairyChannelColors[12];
extern char           D_801D0C10[];
extern char           D_801D0C14[];
extern u16            D_801D0C18[9];
/* D_801D4BB0 */
extern u16            g_FairyRoomMessages[];
/* D_801D4BB8 */
extern u16            g_FairyListMessages[10];
/* D_801D4BCC */
extern Callback       g_Commu01Steps[COMMU01_STEP_COUNT];
/* D_801D4BD8 */
extern Callback       g_Commu01Step2Steps[COMMU01_STEP2_COUNT];
/* D_801D4BE4 */
extern Callback       g_Commu01MoveSteps[];
/* D_801D4BEC */
extern Callback       g_Commu01Step2Sub1Steps[COMMU01_STEP2_SUB1_COUNT];
/* D_801D4C04 */
extern u8             g_FairyListOptionTypes[12];
/* D_801D4C10 */
extern u16            g_FairyOptionMessages[4];
/* D_801D4C18 */
extern u8             g_FairyOptionLines[12][2];
/* The channel each commu record type blinks. */
/* D_801D4C20 */
extern u8             g_FairyBlinkChannels[];
/* The overview's separator text and the icon each room type draws; the shop's icon steps with its stock row. */
extern u8             D_801D4C30[];
/* D_801D4C34 */
extern u8             g_FairyRoomIcons[];
/* D_801D4C44 */
extern CommuCellFrame g_FairyCellFrames[COMMU_CELL_FRAME_COUNT];
/* D_801D4CD4 */
extern u8             g_FairyIconCluts[];
/* D_801D4CE0 */
extern FairyPiece     g_FairyPieces[];
/* D_801D4D34 */
extern u8             g_FairyMenuText[][8];
/* D_801D4DD4 */
extern CommuTypeRows  g_FairyOptionRows[];
/* D_801D4DDA */
extern u16            g_FairyJobMessages[];
/* D_801D4DDC */
extern Pos2u          g_FairyJobSlots[];
/* D_801D4DF4 */
extern u8             g_FairyCursorColumn;
/* D_801D4DF8 */
extern u8             g_FairyCursorGridRow;
/* D_801D4DFC */
extern u8             g_FairyCursorZone;
/* D_801D4E00 */
extern u8             g_FairySavedCursorColumn;
/* D_801D4E04 */
extern u8             g_FairySavedCursorGridRow;
/* D_801D4E08 */
extern u8             g_FairySavedCursorZone;
/* D_801D4E0C */
extern u16            g_FairyMessage;
/* D_801D4E10 */
extern u8             g_FairyReturnStep;
/* D_801D4E14 */
extern u16            g_FairyReturnMessage;
/* D_801D4E18 */
extern u8             g_FairyConfirmChoice;
extern u8             D_801D4E1C;
extern u8             D_801D4E20;
/* D_801D4E24 */
extern u8             g_FairyJobOrdinal;
extern u8             D_801D4E28;
extern u8             D_801D4E2C;
extern u8             D_801D4E30;
extern u8             D_801F286D[];

/* The battle counter that follows the scene event's selection byte; retail loads
 * it off the selection pointer the commu request walks. */
#define COMMU_REQUEST_ANCHOR(rec) (*(u32*)((rec) + 0x73F))

/* func_801D28A4 */
void Fairy_DrawChannelBox(s16 x, s16 y, u8 slot, s32 selected);
/* func_801D2D98 */
void Fairy_DrawChannelBar(s16 x, s16 y, s16 width, u8 channel, u8 blink);
/* func_801D3038 */
void Fairy_DrawOverview(void);
/* func_801D36FC */
void Fairy_DrawCellFrame(s32 cell, s32 selected);
/* func_801D3984 */
void Fairy_DrawCursor(s32 x, s32 y, s32 bright);
u8   Fairy_GetJobActive(u8 job_type);
/* func_801D3AA0 */
u8   Fairy_FindJob(u8 type, u8 index);
/* func_801D3B0C */
void Fairy_MoveCursor(u8* cell);
/* func_801D3EFC */
void Fairy_DrawRoomIcon(s16 x, s16 y, u8 icon);
/* func_801D4030 */
void Fairy_DrawPiece(s16 x, s16 y, u8 piece);
/* func_801D4178 */
void Fairy_DrawTypeMenu(s16 x, s16 y, u8 mode);
/* func_801D44E0 */
s16  Fairy_DrawOptionMenu(s16 x, s16 y, u8 type, u8 mode);
/* func_801D4694 */
void Fairy_GetJobPos(s16* out_x, s16* out_y, s32 type, s32 ordinal);
/* func_801D47C4 */
void Fairy_RestoreCursor(void);
/* func_801D482C */
s32  Fairy_MoveJob(s32 ordinal_offset);
/* func_801D49C4 */
void Fairy_ShowTypeMessage(void);
/* func_801D4AAC */
void Fairy_ShowTargetMessage(u8* target);
/* func_801D4B58 */
void Fairy_AskConfirm(void);

#endif
