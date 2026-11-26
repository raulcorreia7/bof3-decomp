#include "engine/slus/slus.h"

/* Plays the sprite animation once: as Script_AnimStepLoop, but at the end of the stream it sets the delay (+0x4A)
 * to 1 and returns 1 without staging, so the last frame holds.
 */
/* func_8014DAEC */
MATCH u8 Script_AnimStepOnce(void) {
    u8  result;
    u8  count;
    u16 index;

    result              = 0;
    count               = SELF(Actor)->unk_4A - 1;
    SELF(Actor)->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        index = SELF(Actor)->script_pc;
        if ((index >> 1) == SELF(Actor)->unk_49) {
            SELF(Actor)->unk_4A = 1;
            return 1;
        }
        if (*(u8*)(SELF(Actor)->script + index) >= 0x80) {
            SELF(Actor)->script_pc = *(u8*)(SELF(Actor)->script + index + 1) << 1;
            result                 = 1;
        }
        Script_AnimStageStep();
    }
    return result;
}
