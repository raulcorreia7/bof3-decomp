#include "engine/slus/slus.h"

/* latches the g_SndVolumeLevels u16 level-table entries at left_index and right_index
 * into the volume cells D_8018B3D8 (volL) and D_8018B3DC (volR) that
 * SND_SEPlay forwards to SsUtSetDetVVol, then queues SE id se_id.
 */
MATCH void SND_SEQueueVolume(s32 se_id, s32 left_index, s32 right_index) {
    D_8018B3D8 = g_SndVolumeLevels[left_index & HALF_MASK];
    D_8018B3DC = g_SndVolumeLevels[right_index & HALF_MASK];
    SND_SEPlay(se_id & HALF_MASK);
}
