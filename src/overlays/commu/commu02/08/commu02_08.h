#ifndef OVERLAY_ETC_COMMU02_08_H
#define OVERLAY_ETC_COMMU02_08_H

/* The etc/commu02/08 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"

extern u8 D_801457E8[][5];
/* g_EmiOverlayHeader */
extern u8 D_801DAAA8;
/* Entries of the handler tables. */
#define COMMU02_EVENT0_STEP_COUNT       3
#define COMMU02_EVENT0_STEP0_COUNT      2
#define COMMU02_EVENT0_STEP1_COUNT      13
#define COMMU02_EVENT0_STEP1_SUB2_COUNT 3
#define COMMU02_EVENT0_STEP1_SUB3_COUNT 5
#define COMMU02_EVENT1_STEP_COUNT       3
#define COMMU02_EVENT1_STEP0_COUNT      4
#define COMMU02_EVENT1_STEP1_COUNT      9
#define COMMU02_EVENT1_STEP1_SUB0_COUNT 2
#define COMMU02_EVENT2_STEP_COUNT       3
#define COMMU02_EVENT2_STEP0_COUNT      2
#define COMMU02_EVENT2_STEP1_COUNT      5
#define COMMU02_EVENT3_STEP_COUNT       5
#define COMMU02_EVENT3_STEP1_COUNT      9
#define COMMU02_EVENT3_STEP1_SUB6_COUNT 3
#define COMMU02_EVENT3_STEP1_SUB7_COUNT 5
#define COMMU02_EVENT3_STEP2_COUNT      9
#define COMMU02_EVENT3_STEP2_SUB6_COUNT 3
#define COMMU02_EVENT3_STEP2_SUB7_COUNT 5

/* D_801DABCC */
extern Callback g_Commu02Event0States[COMMU02_EVENT0_STEP_COUNT];
/* D_801DABD8 */
extern Callback g_Commu02Event0Step0Funcs[COMMU02_EVENT0_STEP0_COUNT];
/* D_801DABE0 */
extern Callback g_Commu02Event0Step1Funcs[COMMU02_EVENT0_STEP1_COUNT];
/* D_801DAC14 */
extern Callback g_Commu02Event0Step1Sub2Funcs[COMMU02_EVENT0_STEP1_SUB2_COUNT];
/* D_801DAC20 */
extern Callback g_Commu02Event0Step1Sub3Funcs[COMMU02_EVENT0_STEP1_SUB3_COUNT];
/* D_801DACB8 */
extern Callback g_Commu02Event1States[COMMU02_EVENT1_STEP_COUNT];
/* D_801DACC4 */
extern Callback g_Commu02Event1Step0Funcs[COMMU02_EVENT1_STEP0_COUNT];
/* D_801DACD4 */
extern Callback g_Commu02Event1Step1Funcs[COMMU02_EVENT1_STEP1_COUNT];
/* D_801DACF8 */
extern Callback g_Commu02Event1Step1Sub0Funcs[COMMU02_EVENT1_STEP1_SUB0_COUNT];
/* D_801DAD68 */
extern Callback g_Commu02Event2States[COMMU02_EVENT2_STEP_COUNT];
/* D_801DAD74 */
extern Callback g_Commu02Event2Step0Funcs[COMMU02_EVENT2_STEP0_COUNT];
/* D_801DAD7C */
extern Callback g_Commu02Event2Step1Funcs[COMMU02_EVENT2_STEP1_COUNT];
/* D_801DADEC */
extern Callback g_Commu02Event3States[COMMU02_EVENT3_STEP_COUNT];
/* D_801DAE00 */
extern Callback g_Commu02Event3Step1Funcs[COMMU02_EVENT3_STEP1_COUNT];
/* D_801DAE24 */
extern Callback g_Commu02Event3Step1Sub6Funcs[COMMU02_EVENT3_STEP1_SUB6_COUNT];
/* D_801DAE30 */
extern Callback g_Commu02Event3Step1Sub7Funcs[COMMU02_EVENT3_STEP1_SUB7_COUNT];
/* D_801DAE44 */
extern Callback g_Commu02Event3Step2Funcs[COMMU02_EVENT3_STEP2_COUNT];
/* D_801DAE68 */
extern Callback g_Commu02Event3Step2Sub6Funcs[COMMU02_EVENT3_STEP2_SUB6_COUNT];
extern u8       g_MenuPortraitAtlas[];

/* D_801DAE74 */
extern Callback  g_Commu02Event3Step2Sub7Funcs[COMMU02_EVENT3_STEP2_SUB7_COUNT];
extern s32       D_801DB07C;
extern u8        D_801DB058[][5];
extern u8        D_801DB080[];
extern u8        D_801DB089[];
/* The overlay's state byte the guarded step advances. */
extern s8        D_801DB093;
extern u8        D_801DB0AD;
extern u8        D_801DB0AE;
extern u8        D_801DB0B4;
extern s8        D_801DB0B8;
extern u8        D_801DB0C4;
extern u8        D_801DAC60[];
extern u16       D_801DB0C8;
extern u8        D_801DB0CC;
extern u8        D_801DB0D0;
extern u8        D_801DB0D4;
extern u8        D_801DB0D8;
extern u8        D_801DB0DC;
extern u8        D_801F2944;
extern u8        D_801F2945;
extern u8        D_801F294F;
extern char      D_801D0C04[];
extern char      D_801D0C08[];
extern char      D_801D0C10[];
extern char      D_801D0C18[];
extern char      D_801D0C20[];
extern char      D_801D0C24[];
extern char      D_801D0C2C[];
extern u8        D_801D0C30[12];
extern u16       D_801DAC34[2][8];
extern u8        D_801448F2;
extern u8        D_801DACA8[];
extern u8        D_801DACAC[];
extern u8        D_801DACB0[];
extern u8        D_801DACB4[];
extern u8        D_801DAD00[48][2];
extern u8        D_801DAD60[];
extern u8        D_801DAD64[];
extern u8        D_801DAD90[0x48];
extern u8        D_801DADD8[20];
extern u8        D_801DAE88[][6];
extern u8        D_801DB07F;
extern u8        D_801DB0A8[];
extern s8        D_801DB0BC;
extern s8        D_801DB0C0;
extern u8        D_801D0C3C[];
extern u8        D_801DAAAC[];
extern const u8* D_801DB038[];
extern const u8* volatile D_801DB054;

void func_801D2E10(void);
void func_801D2E60(s16 x, s16 y);
/* func_801D7EA0 */
u8   Fairy_FindActiveJob(u8);

u8 Party_GetJoinedCharacter(u8);

s8 func_801DA114();

void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);
void func_801D32A0(s32 x, s32 y, u8 mode);
void func_801D4EA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_801DA8E8(void);

void func_801D2794(s32 count, s32 shown, s32 chosen);
void func_801D2870(void);
void func_801D2AC4(s16 x, s16 y, s32 column, s32 style);
void func_801D2CF8(s32 x, s32 y, s32 icon);
void func_801D3184(s32 x, s32 y);
void func_801D4AE0(s16 x, s16 y, u8 flag);
void func_801D4F88(s32 x, s32 y, s32 show_values);
void func_801D5B2C(void);
void func_801D8058(s32 left, s32 top);
void func_801D830C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
/* The area text bank indexes of the tables the fairy name halves come from. */
#define FAIRY_NAME_FIRST_HALF_INDEX  496
#define FAIRY_NAME_SECOND_HALF_INDEX 560
/* func_801D8968 */
void Fairy_GenerateName(void);
void func_801D90D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_801D94D0(s32 page, s32 left, s32 top, s32 cursor_col_arg, s32 cursor_row_arg);
void func_801D97C8(s32 unused, s32 x, s32 y);
void func_801D9B80(s32 x, s32 y, s32 width, s32 height);
void func_801DA7A4(void);

/* The cell the cursor points at: one 0x60-byte page of eight rows, twelve one-byte cells each. */
static inline u8* Commu02_CursorCell(void) {
    return D_801DAAAC + (D_801DAAA8 * 0x60) + ((s8)D_801DB0D8 * 0xC) + (s8)D_801DB0D4;
}

#endif
