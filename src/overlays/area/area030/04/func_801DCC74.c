#include "area030_04.h"

/* Dispatches through the AREA030 state handler table selected by
 * the global state index byte D_80144286. */
MATCH void func_801DCC74(void) {
    D_801E22E4[D_80144286]();
}
