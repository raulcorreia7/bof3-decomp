#include "engine/slus/slus.h"

/* replays the sound entry selected by cue_id unless cue_id is 0xFF.
 */
MATCH void SND_BGMResume(s32 cue_id) {
    SND_SeqTogglePlayer(SsSepReplay, cue_id);
}
