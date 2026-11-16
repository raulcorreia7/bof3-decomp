#include "logo/logo.h"

MATCH s32 Logo_StartStream(u_long disc_lba) {
    u_long* vlc_data;
    u_long* frame;
    s32     failures;
    s32     mode;
    D_801EB458 = 0;
    D_801EB46C = 0;
    D_801EB464 = 0;
    DecDCTReset(0);
    DecDCToutCallback(Logo_DecodeSlice);
    mode = CdlModeStream | CdlModeSpeed | CdlModeRT | CdlModeSF;
    StSetRing((u_long*)D_801EB448, 15);
    StSetStream(1, 1, 0x0FFFFFFF, 0, 0);
    D_801EB474 = 1;
    D_801EB475 = 1;
    CdIntToPos(disc_lba, (CdlLOC*)&D_801EB4AC);
    failures = 0;
    do {
        if (CdControl(CdlSetfilter, &D_801EB474, 0) == 0) {
            failures++;
        }
        if (CdControl(CdlSetloc, &D_801EB4AC, 0) == 0) {
            failures++;
        }
        if (CdRead2(mode) == 0) {
            failures++;
        }
    } while (failures != 0);
    do {
    } while (StGetNext(&vlc_data, &frame) != 0);
    D_801EB468 = frame[2];
    DecDCTvlc(vlc_data, ((u_long**)&D_801EB44C)[D_801EB458]);
    StFreeRing(vlc_data);
    return 0;
}
