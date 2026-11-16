#include "scena16_00.h"

/* The payload's leading word: the module id the type-0 EMI loader compares
 * against the archive TOC's cached first word (@source: wiki:formats/emi). The jump
 * tables follow at +4. */
OverlayHeader D_801F6C00 = {0x115};
