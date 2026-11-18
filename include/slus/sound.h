#ifndef SLUS_SOUND_H
#define SLUS_SOUND_H

#include "types.h"

/* The executable's sound functions, in address order. */
/* func_8015CD00 */
void        SND_Init(void);
/* func_8015CE70 */
extern void SND_Start(void);
/* func_8015CEBC */
void        SND_Exit(void);
void        SND_StartVolumeSweep(s32 voice);
/* func_8015D300 */
void        SND_PlaySequence(u16 sep_slot, s32 sequence, s32 left_volume, s32 right_volume);
/* func_8015D404 */
void        SND_StopSequence(s32 group, s16 sequence);
/* func_8015D438 */
void        SND_SetSequenceVolume(s32 group, s16 sequence, s16 left_volume, s16 right_volume);
/* func_8015D49C */
void        SND_FadeInSequence(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D4F8 */
void        SND_StartDecrescendo(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D554 */
void        SND_FadeOutSequence(u32 effect_group, s32 effect_id, s32 cue_level, s32 cue_shape);
/* func_8015D5D8 */
void        SND_StopAllSequences(void);
/* func_8015D660 */
bool        SND_TestEffectVoicesBusy(u8* out_index, u8* out_seq);
/* func_8015D71C */
extern void SND_QueueSelectionSE(s32 se_id);
/* func_8015D7C8 */
void        SND_QueueSeVolume(s32 se_id, s32 left_index, s32 right_index);
/* func_8015DF18 */
void        SND_PlaySE(u16 se_id);
/* func_80161808 */
void        SND_SetBankLayout(u32 layout);
/* func_80161B24 */
void        SND_StartBGM(u8 bgm_id, u8 cue_level, u8 cue_shape);
/* func_80161BBC */
bool        SND_RequestBGM(s32 bgm_id);
/* func_80161C20 */
void        SND_PlayBGM(s32 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161CD0 */
void        SND_FadeOutBGM(u8 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161D20 */
void        SND_PauseBGM(s32 cue_id);
/* func_80161D74 */
void        SND_ResumeBGM(s32 cue_id);
/* func_80161DC8 */
void        SND_InstallSequenceFuncs(void);
/* func_801636A0 */
void        SND_StartXAStream(s32 key, s32 unused);
/* func_80163744 */
void        SND_ResolveXAStream(s32 stream_id);
/* func_80163858 */
void        SND_StoreXASyncResult(s32 intr, u8* result);
/* func_801638B0 */
void        SND_UpdateXA(void);
/* func_801639B8 */
void        SND_XAStateIdle(void);
/* func_801639D0 */
void        SND_XAStateSeek(void);
/* func_80163A54 */
void        SND_XAStateSeekResult(void);
/* func_80163AF0 */
void        SND_XAStateRead(void);
/* func_80163B74 */
void        SND_XAStateReadProgress(void);
/* func_80163C58 */
void        SND_XAStateReadResult(void);
/* func_80163D20 */
void        SND_XAStatePause(void);
/* func_80163D80 */
void        SND_XAStatePauseResult(void);
/* func_80163E3C */
void        SND_XAStateWaitSync(void);
/* func_80163E88 */
bool        SND_HasXACDError(void);
/* func_80163EA0 */
u8          SND_IsXAIdle(void);
/* func_80163EB0 */
void        SND_SetCDVolume(u8 volume);
/* func_80163F50 */
void        SND_FadeCDVolume(s32 level);

#endif
