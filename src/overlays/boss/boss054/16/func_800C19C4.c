#include "boss054_16.h"

MATCH void func_800C19C4(void) {
    Boss054Funcs handlers;

    handlers = D_800C1804;
    handlers.handlers[((PartyMember*)g_Task)->header.mode]();
}
