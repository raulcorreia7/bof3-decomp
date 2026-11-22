#include "engine/slus/slus.h"

/* seeks the CD reader and flags completion.
 */
MATCH void CD_Seek(void) {
    u16* counter;

    counter = &D_80146492;
    if (*counter != 0) {
        *counter -= 1;
        return;
    }
    /* Param is D_80146778 (CdlLOC; see EMI_ArchiveStart.c); object form regresses
     * bytes. */
    if (CdSeekP((u_char*)counter + 0x2E6) != 0) {
        g_CdState = CD_STATE_SEEK_WAIT;
    }
}
