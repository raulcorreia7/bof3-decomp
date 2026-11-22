#ifndef OVERLAY_SOUND_XA_H
#define OVERLAY_SOUND_XA_H

#include "types.h"

/* func_801636A0 */
void SND_XAStartStream(s32 key, s32 unused);
/* func_80163744 */
void SND_XAResolveStream(s32 stream_id);
/* func_80163858 */
void SND_XASetSyncResult(s32 intr, u8* result);
/* func_801638B0 */
void SND_XAUpdate(void);
/* func_801639B8 */
void SND_XAStateIdle(void);
/* func_801639D0 */
void SND_XAStateSeek(void);
/* func_80163A54 */
void SND_XAStateSeekResult(void);
/* func_80163AF0 */
void SND_XAStateRead(void);
/* func_80163B74 */
void SND_XAStateReadProgress(void);
/* func_80163C58 */
void SND_XAStateReadResult(void);
/* func_80163D20 */
void SND_XAStatePause(void);
/* func_80163D80 */
void SND_XAStatePauseResult(void);
/* func_80163E3C */
void SND_XAStateWaitSync(void);
/* func_80163E88 */
bool SND_XAHasCDError(void);
/* func_80163EA0 */
u8   SND_XAIsIdle(void);
/* func_80163EB0 */
void SND_SetCDVolume(u8 volume);
/* func_80163F50 */
void SND_FadeCDVolume(s32 level);

#endif
