#include "engine/slus/slus.h"

/* installs SetAutoPan as the per-voice auto-pan callback _SsVmFlush runs and starts a pan sweep on `voice`
 * from pan_from to pan_to in delta-sized steps (a voice outside 0..0x17 is rejected). Returns 0, or -1 for a rejected voice.
 */
MATCH short SsUtAutoPan(short voice, short pan_from, short pan_to, short delta) {
    D_8018E7D4 = (s32)SetAutoPan;
    if ((u16)voice < 0x18) {
        SeAutoPan(voice, pan_from, pan_to, delta);
        return 0;
    }
    return -1;
}
