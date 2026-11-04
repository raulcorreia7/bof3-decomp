#include "engine/slus/slus.h"

/* polls the key-on status of every SPU voice 0..0x17 through
 * SpuGetKeyStatus and stores each result in the D_8018E140 table.
 */
MATCH void SND_UpdateVoiceStatus(void) {
    u8 i;

    for (i = 0; i < 24; i++) {
        D_8018E140[i] = SpuGetKeyStatus(1 << i);
    }
}
