#include "engine/slus/slus.h"

/* starts one disc read sized from a byte count and waits until the
 * read finishes or returns a terminal status.
 */
MATCH s32 SYS_ReadCd(s32 size, void* buffer, s32 sectors) {
    s32 sector_count;
    s32 status;

    sector_count = size + 0x7FF;
    if (sector_count < 0) {
        sector_count = size + 0xFFE;
    }

    CdRead(sector_count >> 11, buffer, sectors);

    while (1) {
        status = CdReadSync(1, NULL);
        if (status <= 0) {
            return status;
        }

        VSync(0);
    }
}
