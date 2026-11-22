#include "battle_03.h"

/* func_801E52F0 */
MATCH void Battle_PlayEnemySE(u16 se_id) {
    u16 masked_id;

    masked_id = se_id & HALF_MASK;
    if (masked_id != 0xFFFFu) {
        SND_SEPlay(masked_id);
    }
}
