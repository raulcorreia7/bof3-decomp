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
extern Callback g_Commu02Event0Steps[COMMU02_EVENT0_STEP_COUNT];
/* D_801DABD8 */
extern Callback g_Commu02Event0Step0Steps[COMMU02_EVENT0_STEP0_COUNT];
/* D_801DABE0 */
extern Callback g_Commu02Event0Step1Steps[COMMU02_EVENT0_STEP1_COUNT];
/* D_801DAC14 */
extern Callback g_Commu02Event0Step1Sub2Steps[COMMU02_EVENT0_STEP1_SUB2_COUNT];
/* D_801DAC20 */
extern Callback g_Commu02Event0Step1Sub3Steps[COMMU02_EVENT0_STEP1_SUB3_COUNT];
/* D_801DACB8 */
extern Callback g_Commu02Event1Steps[COMMU02_EVENT1_STEP_COUNT];
/* D_801DACC4 */
extern Callback g_Commu02Event1Step0Steps[COMMU02_EVENT1_STEP0_COUNT];
/* D_801DACD4 */
extern Callback g_Commu02Event1Step1Steps[COMMU02_EVENT1_STEP1_COUNT];
/* D_801DACF8 */
extern Callback g_Commu02Event1Step1Sub0Steps[COMMU02_EVENT1_STEP1_SUB0_COUNT];
/* D_801DAD68 */
extern Callback g_Commu02Event2Steps[COMMU02_EVENT2_STEP_COUNT];
/* D_801DAD74 */
extern Callback g_Commu02Event2Step0Steps[COMMU02_EVENT2_STEP0_COUNT];
/* D_801DAD7C */
extern Callback g_Commu02Event2Step1Steps[COMMU02_EVENT2_STEP1_COUNT];
/* D_801DADEC */
extern Callback g_Commu02Event3Steps[COMMU02_EVENT3_STEP_COUNT];
/* D_801DAE00 */
extern Callback g_Commu02Event3Step1Steps[COMMU02_EVENT3_STEP1_COUNT];
/* D_801DAE24 */
extern Callback g_Commu02Event3Step1Sub6Steps[COMMU02_EVENT3_STEP1_SUB6_COUNT];
/* D_801DAE30 */
extern Callback g_Commu02Event3Step1Sub7Steps[COMMU02_EVENT3_STEP1_SUB7_COUNT];
/* D_801DAE44 */
extern Callback g_Commu02Event3Step2Steps[COMMU02_EVENT3_STEP2_COUNT];
/* D_801DAE68 */
extern Callback g_Commu02Event3Step2Sub6Steps[COMMU02_EVENT3_STEP2_SUB6_COUNT];
extern u8       g_MenuPortraitAtlas[];
extern u8       D_801448F2;
extern char     D_801D0C04[];
extern char     D_801D0C08[];
extern char     D_801D0C10[];
extern char     D_801D0C18[];
extern char     D_801D0C20[];
extern char     D_801D0C24[];
extern char     D_801D0C2C[];
extern u8       D_801D0C30[12];
extern u8       D_801D0C3C[];
extern u8       D_801DAAAC[][8][12]; /* name entry grid: pages of 8 rows by 12 cells */
extern u16      D_801DAC34[2][8];
/* The three 4-byte column labels drawn by func_801D2AC4. */
extern u8       D_801DAC54[3][4];
extern u8       D_801DAC60[];
extern u8       D_801DACA8[];
extern u8       D_801DACAC[];
extern u8       D_801DACB0[];
extern u8       D_801DACB4[];
extern u8       D_801DAD00[48][2];
extern u8       D_801DAD60[];
extern u8       D_801DAD64[];
/* The eight board layouts: up to nine digit rows each, a 9 ends the layout. */
extern u8       D_801DAD90[8][9];
/* The numbers board's four digits, a message-run base byte then the limit the
 * round picks under. */
extern u8       D_801DADD8[4][2];
/* The four board rounds: the weight the random pick compares, then the two digit
 * rows the round shows. 0xFF in the second row means the round shows one digit. */
extern u8       D_801DADE0[4][3];

/* D_801DAE74 */
extern Callback  g_Commu02Event3Step2Sub7Steps[COMMU02_EVENT3_STEP2_SUB7_COUNT];
extern u8        D_801DAE88[][6];
extern const u8* D_801DB038[];
extern const u8* volatile D_801DB054;
extern u8  D_801DB058[][5];
extern s32 D_801DB07C;
extern u8  D_801DB07F;

/* The overlay's scratch bytes: the Numbers row, the fairy name, and the words each category already gave. */
typedef union Commu02Scratch {
    u8 bytes[0x2C];

    struct {
        u8 picked[4 * 10]; /* ten words per category, in the order given */
        u8 count[4];
    } words;
} Commu02Scratch;

extern Commu02Scratch D_801DB080;
extern u8             D_801DB089[];
/* The overlay's state byte the guarded step advances. */
extern s8             D_801DB093;
extern u8             D_801DB0AD;
extern u8             D_801DB0AE;
extern u8             D_801DB0B4;
extern s8             D_801DB0B8;
extern s8             D_801DB0BC;
extern s8             D_801DB0C0;
extern u8             D_801DB0C4;
extern u16            D_801DB0C8;
extern u8             D_801DB0CC;
extern u8             D_801DB0D0;
extern u8             D_801DB0D4;
extern u8             D_801DB0D8;
extern u8             D_801DB0DC;
extern u8             D_801F2944;
extern u8             D_801F2945;
extern u8             D_801F294F;

void func_801D2794(s32 count, s32 shown, s32 chosen);
void func_801D2870(void);
void func_801D2AC4(s16 x, s16 y, u8 column, u8 style);

u8 Party_GetJoinedCharacter(u8);

void func_801D2CF8(s32 x, s32 y, s32 icon);

void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);
void func_801D2E10(void);
void func_801D2E60(s16 x, s16 y);
void func_801D3184(s32 x, s32 y);

void func_801D32A0(s32 x, s32 y, u8 mode);
void func_801D4AE0(s16 x, s16 y, u8 flag);
void func_801D4EA4(s16 left, s16 top, u8 icon_row, u8 raised);
void func_801D4F88(s32 x, s32 y, s32 show_values);
/* func_801D5AD0 */
s32  func_801D5AD0(s32 limit);
void func_801D5B2C(void);
/* func_801D7EA0 */
u8   Fairy_FindActiveJob(u8);
void func_801D8058(s32 left, s32 top);
s8   func_801DA114();
void func_801DA8E8(void);
void func_801D830C(s32 x, s32 y, u8 kind, u8 mode);
/* The area text bank indexes of the tables the fairy name halves come from. */
#define FAIRY_NAME_FIRST_HALF_INDEX  496
#define FAIRY_NAME_SECOND_HALF_INDEX 560
/* func_801D8968 */
void Fairy_GenerateName(void);
void func_801D90D8(s32 x, s32 y, s32 character, s32 frame_mode);
void func_801D9348(u16 x, u16 y, s32 color, s32 frame_mode);
void func_801D94D0(s32 page, s32 left, s32 top, s32 cursor_col, s32 cursor_row);
void func_801D97C8(s32 unused, s32 x, s32 y);
void func_801D9B80(s32 x, s32 y, s32 width, s32 height);
void func_801DA7A4(void);

/* Stop the current selection BGM and request the scene cue once the scene is free, then play it when
 * the overlay is ready and step the scene event. A statement macro: the member declares s32 bgm_offset
 * and u8* step. */
#define COMMU02_START_SCENE_BGM()                                                              \
    if (D_801F294D == 0) {                                                                     \
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {                                        \
            bgm_offset = g_SndBGMId * 4;                                                       \
            SND_SeqStop(g_SelectionSepSlots[bgm_offset], g_SelectionSepSlots[bgm_offset + 1]); \
            SND_BGMRequest(D_801DB0CC);                                                        \
            D_801F294D += 1;                                                                   \
        }                                                                                      \
    } else if (EMI_IsReady() != 0) {                                                           \
        SND_BGMPlay(D_801DB0CC, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);                 \
        step  = &g_SceneEventState.step;                                                       \
        *step = *step + 1;                                                                     \
    }

#endif
