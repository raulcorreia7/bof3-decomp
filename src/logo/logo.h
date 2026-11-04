#ifndef LOGO_H
#define LOGO_H

/* The logo player's local declarations: its retail entry points, the stream and
 * MDEC state, and the data symbols its units share. Only this executable
 * includes the file. */

#include "game.h"
#include "sys/intr.h"
#include <libpress.h>

/* retail addresses */
#define LOGO_WORK_BASE 0x8003B800 /* the work area Logo_Init carves at +0x2D00/+0xA500/+0x10480 */

/* Data, in address order. */
extern u_long         D_801D8BB0; /* CAPCOM30.STR base LBA used by the LOGO.EXE scheduler */
extern u32            D_801EB424;
extern void*          D_801EB428;
extern void*          D_801EB42C;
extern u8             D_801EB440;
extern u_long*        D_801EB444;
extern s32            D_801EB448;
extern s32            D_801EB44C;
extern s32            D_801EB450;
extern s32            D_801EB454;
extern s32            D_801EB458;
extern RECT           D_801EB45C; /* MDEC output window (x, y, w, h) */
extern s32            D_801EB464;
extern s32            D_801EB468;
extern volatile s32   D_801EB46C; /* polled move flag; SYSTEM_LogoDecodeSlice writes it from the DecDCTout callback */
extern u8             s_LogoCdVolume[4];
extern s8             D_801EB474;
extern s8             D_801EB475;
extern DISPENV        D_801EB480[2];
extern u8             D_801EB491;
extern u8             D_801EB4A5;
extern s32            D_801EB4A8;
extern s8             D_801EB4AC;
extern s32            D_801EB650;
extern InterruptHooks D_801EB654;
extern s32            D_801EB678;

/* Functions, in address order. */
void Logo_Init(s32 work_base, u_long disc_lba);
void Logo_InitDisplay(void);
void Logo_FlipDisplay(void);
s32  Logo_StartStream(u_long disc_lba);
s32  Logo_DrawFrame(void);
void Logo_StopStream(void);
void Logo_WaitFrame(void);
void Logo_DecodeSlice(void);
s32  Logo_FadeInAudio(void);
void Logo_FadeOutAudio(void);
void Logo_Main(void);

#endif
