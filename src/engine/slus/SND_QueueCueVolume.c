#include "engine/slus/slus.h"

/* latches the D_80182288 u16 level-table entries at left_index and right_index
 * into the volume cells D_8018B3D8 (volL) and D_8018B3DC (volR) that
 * SND_PlayCue forwards to SsUtSetDetVVol, then queues cue id cue_id.
 */
MATCH void SND_QueueCueVolume(s32 cue_id, s32 left_index, s32 right_index) {
    D_8018B3D8 = D_80182288[left_index & HALF_MASK];
    D_8018B3DC = D_80182288[right_index & HALF_MASK];
    SND_PlayCue(cue_id & HALF_MASK);
}
