#include "engine/slus/slus.h"

/* latches the g_SndVolumeLevels u16 level-table entries at left_index and right_index
 * into the volume cells g_SndSeVolumeL (volL) and g_SndSeVolumeR (volR) that
 * SND_SEPlay forwards to SsUtSetDetVVol, then queues SE id se_id.
 */
MATCH void SND_SEQueueVolume(s32 se_id, s32 left_index, s32 right_index) {
    g_SndSeVolumeL = g_SndVolumeLevels[left_index & HALF_MASK];
    g_SndSeVolumeR = g_SndVolumeLevels[right_index & HALF_MASK];
    SND_SEPlay(se_id & HALF_MASK);
}
