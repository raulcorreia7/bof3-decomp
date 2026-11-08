#include "battle_03.h"

/* func_801E52F0 */
MATCH void Battle_PlayEnemyCue(u16 cue_id) {
    u16 masked_id;

    masked_id = cue_id & HALF_MASK;
    if (masked_id != 0xFFFFu) {
        SND_PlayCue(masked_id);
    }
}
