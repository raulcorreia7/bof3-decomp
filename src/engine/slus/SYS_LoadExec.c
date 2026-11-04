#include "engine/slus/slus.h"

typedef struct {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
} SystemWord4;

/* reads one EXE file into RAM in two sector-sized steps and copies
 * the first staged header block into the boot scratch area.
 */
MATCH s32 SYS_LoadExec(const char* path) {
    const char* current_path;
    s32         sectors;
    s32         attempts;
    s32*        exe_size;
    CdlFILE     file;
    u32*        src;
    u32*        dst;

    current_path = path;
    sectors      = 0x80;
    attempts     = 0;
    exe_size     = (s32*)&D_80143E8C;

    for (;;) {
        if (CdSearchFile(&file, (char*)current_path) != NULL) {
            CdControl(CdlSetloc, (u_char*)&file, NULL);
            if (SYS_ReadCd(0x800, D_801459F8, sectors) == 0) {
                SystemWord4* s = (SystemWord4*)D_801459F8;
                SystemWord4* d = (SystemWord4*)D_80143E70;
                SystemWord4* e = s + 8;
                u32          w0;
                u32          w1;

                do {
                    *d++ = *s++;
                } while (s != e);

                w0    = s->w0;
                w1    = s->w1;
                d->w0 = w0;
                d->w1 = w1;
                /* FAKE: barrier orders word-copy ahead of CD call. */
                MATCH_BARRIER();

                CdIntToPos(CdPosToInt(&file.pos) + 1, &file.pos);
                CdControlB(CdlSetloc, (u_char*)&file, NULL);

                if (SYS_ReadCd(exe_size[0], (void*)exe_size[-1], sectors) == 0) {
                    attempts += 1;
                    return 0;
                }
            }
        }

        attempts += 1;
        if (attempts >= 10) {
            return -1;
        }
    }
}
