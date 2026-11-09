#include "slus.h"
/* The 0x80181BDC table is declared by the image header; this data unit needs
 * only the record type, so it names the base table it points into. */

/*
 * start of each list inside D_80181BDC; func_8014D6DC selects an entry
 * by the scratchpad work index.
 */

const ScriptRef *const D_80181C7C[11] = {
    &D_80181BDC[0],  &D_80181BDC[10], &D_80181BDC[15], &D_80181BDC[20], &D_80181BDC[21], &D_80181BDC[29],
    &D_80181BDC[30], &D_80181BDC[31], &D_80181BDC[34], &D_80181BDC[35], &D_80181BDC[39],
};
