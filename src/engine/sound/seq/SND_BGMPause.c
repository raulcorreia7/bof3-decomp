#include "engine/slus/slus.h"

/* pauses the sequence player for the sound entry selected by cue_id unless
 * cue_id is 0xFF.
 */
MATCH void SND_BGMPause(s32 cue_id) {
    Snd_ToggleSequencePlayer(SsSepPause, cue_id);
}
