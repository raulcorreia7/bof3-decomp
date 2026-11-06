#include "battle_03.h"

MATCH void func_801E52F0(u16 effect_id) {
    u16 masked_id;

    masked_id = effect_id & 0xFFFF;
    if (masked_id != 0xFFFFu) {
        SND_PlayCue(masked_id);
    }
}
