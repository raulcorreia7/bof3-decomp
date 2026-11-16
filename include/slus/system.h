#ifndef SLUS_SYSTEM_H
#define SLUS_SYSTEM_H

#include "types.h"
#include "sys/cd_format.h"
#include "common/handler.h"

/* The executable's system, archive, input and decompression functions, in address order. */
/* func_8014AEE0 */
void        SYS_StartLogo(void);
/* func_8014AFC0 */
void        SYS_UpdateKeyState(void);
/* func_8014B020 */
void        SYS_PrepareFrame(void);
/* func_8014B0F0 */
void        SYS_SubmitFrame(void);
/* func_8014B17C */
void        SYS_CaptureDrawTime(void);
/* func_8014B1A4 */
extern void SYS_InitCard(void);
/* func_8014B33C */
void        SYS_ThreadStopAll(void);
/* func_8014B3C4 */
extern void SYS_ShowException(void);
/* func_8014B6B4 */
void        SYS_ThreadInit(void);
/* func_8014B73C */
void        SYS_ThreadRun(void);
/* func_8014B854 */
void        SYS_ThreadRegister(s32 thread_index, Callback callback);
/* func_8014B87C */
void        SYS_ThreadWait(u16 countdown);
/* func_8014B8B0 */
void        SYS_ThreadExit(void);
/* func_8014B900 */
void        SYS_ThreadClose(s32 thread_index);
/* func_8014B954 */
extern void SYS_ThreadReplace(Callback entry);
/* func_8014E0A8 */
extern s32  SYS_ReadCD(s32 size, void* buffer, s32 sectors);
/* func_8014E640 */
s32         INPUT_GetRepeatedButtons(s32 button_mask);
/* func_8014EA80 */
void        SYS_StartFrontend(void);
/* func_8014EC64 */
void        SYS_EnterFrontend(void);
/* func_801501E4 */
void        SYS_CopyString(u8* dst, u8* src, s32 limit);
/* SYS_InitScratchpad */
/* func_8015AC8C */
void        SYS_InitScratchpad(u8* panel);
/* func_8015B580 */
void        SYS_SetFlag(void* bits, u8 bit_index);
/* func_8015B5A8 */
void        SYS_ClearFlag(void* bits, u8 bit_index);
/* func_8015B5D4 */
s32         SYS_TestFlag(void* bits, s32 bit_index);
/* func_8015B5F4 */
void        SYS_ToggleFlag(void* bits, u8 bit_index);
/* func_80161F58 */
void        EMI_Init(void);
/* func_80161FDC */
void        EMI_LoadArchive(u32 emi_id);
/* func_80162160 */
DiscLba     EMI_GetArchiveSector(EMISlotId emi_id);
/* func_80162178 */
void        EMI_StartArchive(void);
/* func_801621E8 */
void        EMI_CdOnSync(s32 status, u8* result);
/* func_80162230 */
void        EMI_CdOnReady(u8 status, u8* result);
/* func_80162C14 */
void        EMI_CopySector(void);
/* func_80162CD8 */
void        EMI_EndArchive(void);
/* func_80162D00 */
bool        EMI_IsReady(void);
/* func_80162D18 */
void        EMI_CdUpdate(void);
/* func_80162D9C */
void        EMI_CdIdle(void);
/* func_80162DA4 */
void        EMI_CdSetSpeed(void);
/* func_80162E18 */
void        EMI_CdSeek(void);
/* func_80162E70 */
void        EMI_CdOnSeek(void);
/* func_80162E98 */
void        EMI_CdRead(void);
/* func_80162F04 */
void        EMI_CdOnRead(void);
/* func_80162F34 */
void        EMI_CdPause(void);
/* func_80162F88 */
void        EMI_CdOnPause(void);
/* func_8016305C */
void        EMI_UpdateStream(void);
/* func_80163238 */
void        EMI_DecompressSector(void);
/* func_8016327C */
void        EMI_CopySectorToScratchpad(void);
/* func_80163378 */
void        EMI_UploadSectorImage(void);
/* func_80163418 */
void        EMI_UploadVabBody(void);
/* func_80164028 */
void        LZ77_DecodeBegin(u8* dst);
/* func_80164064 */
s32         LZ77_DecodeStep(void);
/* func_80166E88 */
void        EMI_LoadPartyArchives(u8 member_a, u8 member_b, u8 member_c, u8 family);
/* func_8016728C */
void        EMI_GetArchiveId(u8 index, u8 family);

#endif
