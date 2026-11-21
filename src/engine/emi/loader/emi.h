#ifndef OVERLAY_EMI_LOADER_H
#define OVERLAY_EMI_LOADER_H

#include "types.h"
#include "sys/cd_format.h"

/* func_80161F58 */
void    EMI_Init(void);
/* func_80161FDC */
void    EMI_LoadArchive(u32 emi_id);
/* func_80162160 */
DiscLba EMI_GetArchiveSector(EMISlotId emi_id);
/* func_80162178 */
void    EMI_StartArchive(void);
/* func_801621E8 */
void    EMI_CdOnSync(s32 status, u8* result);
/* func_80162230 */
void    EMI_CdOnReady(u8 status, u8* result);
/* func_80162C14 */
void    EMI_CopySector(void);
/* func_80162CD8 */
void    EMI_EndArchive(void);
/* func_80162D00 */
bool    EMI_IsReady(void);
/* func_80162D18 */
void    EMI_CdUpdate(void);
/* func_80162D9C */
void    EMI_CdIdle(void);
/* func_80162DA4 */
void    EMI_CdSetSpeed(void);
/* func_80162E18 */
void    EMI_CdSeek(void);
/* func_80162E70 */
void    EMI_CdOnSeek(void);
/* func_80162E98 */
void    EMI_CdRead(void);
/* func_80162F04 */
void    EMI_CdOnRead(void);
/* func_80162F34 */
void    EMI_CdPause(void);
/* func_80162F88 */
void    EMI_CdOnPause(void);
/* func_8016305C */
void    EMI_UpdateStream(void);
void    func_80163230(void);
/* func_80163238 */
void    EMI_DecompressSector(void);
/* func_8016327C */
void    EMI_CopySectorToScratchpad(void);
/* func_80163378 */
void    EMI_UploadSectorImage(void);
/* func_80163418 */
void    EMI_UploadVabBody(void);
void    EMI_ReadToc(void);
void    EMI_LoadToRam(void);
void    EMI_LoadCompressed(void);
void    EMI_LoadToVram(void);
void    EMI_LoadVabHeader(void);
void    EMI_LoadVabBody(void);
void    EMI_LoadSE(void);
void    EMI_LoadSequence(void);
s32     EMI_NextEntry(u8 slot);
void    EMI_Update(void);
/* func_80166E88 */
void    EMI_LoadPartyArchives(u8 member_a, u8 member_b, u8 member_c, u8 family);
/* func_8016728C */
void    EMI_LoadFamilyArchive(u8 index, u8 family);
void    EMI_LoadPartyCode(u8 member_a, u8 member_b, u8 member_c);
void    EMI_LoadParty(u8 member_a, u8 member_b, u8 member_c, u8 family);
u8      EMI_FindPartyArchive(u8 member_a, u8 member_b, u8 member_c);

#endif
