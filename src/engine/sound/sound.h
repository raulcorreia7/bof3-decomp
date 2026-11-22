#ifndef OVERLAY_SOUND_SOUND_H
#define OVERLAY_SOUND_SOUND_H

#include "types.h"
/* The executable's sound functions, in address order. */
/* func_8015CD00 */
void        SND_Init(void);
/* func_8015CE70 */
extern void SND_Start(void);
/* func_8015CEBC */
void        SND_Exit(void);

/* func_8015D104 */
void        SND_VoiceDecreaseTargetVolume(s32 slot, s32 amount);
void        SND_StartVolumeSweep(s32 voice);
/* func_8015D300 */
void        SND_SeqPlay(u16 sep_slot, s32 sequence, s32 left_volume, s32 right_volume);
/* func_8015D404 */
void        SND_SeqStop(s32 group, s16 sequence);
/* func_8015D438 */
void        SND_SeqSetVolume(s32 group, s16 sequence, s16 left_volume, s16 right_volume);
/* func_8015D49C */
void        SND_SeqFadeIn(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D4F8 */
void        SND_StartDecrescendo(s32 group, s16 sequence, s16 volume, s32 time);
/* func_8015D554 */
void        SND_SeqFadeOut(u32 effect_group, s32 effect_id, s32 cue_level, s32 cue_shape);
/* func_8015D5D8 */
void        SND_SeqStopAll(void);
/* func_8015D660 */
bool        SND_VoiceTestEffectsBusy(u8* out_index, u8* out_seq);
/* func_8015D71C */
extern void SND_SEQueueSelection(s32 se_id);
/* func_8015D7C8 */
void        SND_SEQueueVolume(s32 se_id, s32 left_index, s32 right_index);
/* func_8015DF18 */
void        SND_SEPlay(u16 se_id);
/* func_8015E994 */
void        SND_SEReadBank0(void);
/* func_8015EFAC */
void        SND_SEReadBank1(void);
/* func_8015F5C8 */
void        SND_SEReadBank2(void);
/* func_8015FBE4 */
void        SND_SEReadBank3(void);
/* func_80160200 */
void        SND_SEReadBank4(void);
/* func_8016081C */
void        SND_SEReadBank5(void);
/* func_80160E38 */
void        SND_SEReadBank6(void);
extern void func_80161454(u32 index);
/* func_80161808 */
void        SND_SetBankLayout(u32 layout);
/* func_80161B24 */
void        SND_BGMStart(u8 bgm_id, u8 cue_level, u8 cue_shape);
/* func_80161BBC */
bool        SND_BGMRequest(s32 bgm_id);
/* func_80161C20 */
void        SND_BGMPlay(s32 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161CD0 */
void        SND_BGMFadeOut(u8 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161D20 */
void        SND_BGMPause(s32 cue_id);
/* func_80161D74 */
void        SND_BGMResume(s32 cue_id);
/* func_80161DC8 */
void        SND_SeqInstallFuncs(void);
void        SND_VoiceUpdateStatus(void);

#endif
