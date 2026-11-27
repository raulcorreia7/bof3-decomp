#include "boss054_16.h"

MATCH void func_800C19C4(void) {
    Boss054Modes handlers;

    handlers = D_800C1804;
    handlers.modes[SELF(PartyMember)->header.mode]();
}
