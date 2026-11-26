#include "area168_13.h"

MATCH void Fishing_ShowLocation(void) {
    SYS_DISPATCH_BYTE(D_801F4B2C + 0xC, SELF(Actor)->header.mode);
}
