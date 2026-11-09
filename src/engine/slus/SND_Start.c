#include "engine/slus/slus.h"

/* starts the sound system, sets master volume to 0x7F, enables the serial attribute. */
MATCH void SND_Start(void) {
    SsStart2();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);
    SsSetSerialVol(SS_SERIAL_A, 0x6E, 0x6E);
}
