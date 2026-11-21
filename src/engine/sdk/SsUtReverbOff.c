#include "engine/slus/slus.h"

/* turns the SPU reverb unit off.
 */
MATCH void SsUtReverbOff(void) {
    SpuSetReverb(SPU_OFF);
}
