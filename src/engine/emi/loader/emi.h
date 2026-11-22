#ifndef OVERLAY_EMI_LOADER_H
#define OVERLAY_EMI_LOADER_H

#include "types.h"
#include "sys/cd_format.h"

/* func_80161F58 */
void    EMI_Init(void);
/* func_80161FDC */
void    EMI_ArchiveLoad(u32 emi_id);
/* func_80162160 */
DiscLba EMI_ArchiveGetSector(EMISlotId emi_id);
/* func_80162178 */
void    EMI_ArchiveStart(void);
/* func_801621E8 */
void    CD_OnSync(s32 status, u8* result);
/* func_80162230 */
void    CD_OnReady(u8 status, u8* result);
/* func_80162C14 */
void    EMI_SectorCopy(void);
/* func_80162CD8 */
void    EMI_ArchiveEnd(void);
/* func_80162D00 */
bool    EMI_IsReady(void);
/* func_80162D18 */
void    CD_Update(void);
/* func_80162D9C */
void    CD_Idle(void);
/* func_80162DA4 */
void    CD_SetSpeed(void);
/* func_80162E18 */
void    CD_Seek(void);
/* func_80162E70 */
void    CD_OnSeek(void);
/* func_80162E98 */
void    CD_Read(void);
/* func_80162F04 */
void    CD_OnRead(void);
/* func_80162F34 */
void    CD_Pause(void);
/* func_80162F88 */
void    CD_OnPause(void);
/* func_8016305C */
void    EMI_UpdateStream(void);
void    func_80163230(void);
/* func_80163238 */
void    EMI_SectorDecompress(void);
/* func_8016327C */
void    EMI_SectorCopyToScratchpad(void);
/* func_80163378 */
void    EMI_SectorUploadImage(void);
/* func_80163418 */
void    EMI_VabUploadBody(void);
void    EMI_ReadToc(void);
void    EMI_LoadToRam(void);
void    EMI_LoadCompressed(void);
void    EMI_LoadToVram(void);
void    EMI_VabLoadHeader(void);
void    EMI_VabLoadBody(void);
void    EMI_LoadSE(void);
void    EMI_LoadSequence(void);
s32     EMI_NextEntry(u8 slot);
void    EMI_Update(void);
/* func_80166E88 */
void    EMI_PartyLoadArchives(u8 member_a, u8 member_b, u8 member_c, u8 family);
/* func_8016728C */
void    EMI_ArchiveLoadFamily(u8 index, u8 family);
void    EMI_PartyLoadCode(u8 member_a, u8 member_b, u8 member_c);
void    EMI_PartyLoad(u8 member_a, u8 member_b, u8 member_c, u8 family);
u8      EMI_PartyFindArchive(u8 member_a, u8 member_b, u8 member_c);

#endif
