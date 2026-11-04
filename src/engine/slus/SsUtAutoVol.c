#include "engine/slus/slus.h"

/* installs SetAutoVol as the per-voice auto-volume callback _SsVmFlush runs and starts a volume sweep on
 * `voice` from vol_from to vol_to in delta-sized steps (a voice outside 0..0x17 is rejected).
 */
MATCH short SsUtAutoVol(short voice, short vol_from, short vol_to, short delta) {
    D_8018E988 = (s32)SetAutoVol;
    if ((u16)voice < 0x18) {
        SeAutoVol(voice, vol_from, vol_to, delta);
        return 0;
    }
    return -1;
}
