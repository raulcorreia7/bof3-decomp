#include "engine/slus/slus.h"
#include "common/copy.h"

/* reads one EXE file into RAM in two sector-sized steps and copies
 * the first staged header block into the boot scratch area.
 */
MATCH s32 SYS_LoadExe(const char* path) {
    const char* current_path;
    s32         sectors;
    s32         attempts;
    u32*        exe_size;
    CdlFILE     file;
    u32*        src;
    u32*        dst;

    current_path = path;
    sectors      = 0x80;
    attempts     = 0;
    exe_size     = &g_LogoHeader.exec.t_size;

    for (;;) {
        if (CdSearchFile(&file, (char*)current_path) != NULL) {
            CdControl(CdlSetloc, (u_char*)&file, NULL);
            if (SYS_ReadCd(EMI_SECTOR_SIZE, g_SysSectorBuffer, sectors) == 0) {
                Cpy16* s = (Cpy16*)g_SysSectorBuffer;
                Cpy16* d = (Cpy16*)&g_LogoHeader;
                Cpy16* e = s + 8;
                u32    w0;
                u32    w1;

                do {
                    *d++ = *s++;
                } while (s != e);

                w0      = s->w[0];
                w1      = s->w[1];
                d->w[0] = w0;
                d->w[1] = w1;
                /* FAKE: barrier orders word-copy ahead of CD call. */
                FAKE_BARRIER();

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
