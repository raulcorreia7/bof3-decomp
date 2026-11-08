#include "logo/logo.h"

/* func_801CEA98 */
MATCH s32 Logo_DrawFrame(void) { /* func_801CEA98 */
    u_long* vlc_data;
    u_long* frame;
    u_long* next_buf;
    s32     ret;
    s32     y;
    s32     i;
    s32     size;
    s32     next;

    y = (D_801EB4A8 != 0) ? 0xF0 : 0;
    i = 0x100000;
    while (StGetNext(&vlc_data, &frame) != 0) {
        if (--i == 0) {
            return 1;
        }
    }
    size         = frame[2];
    D_801EB45C.w = 24;
    D_801EB464   = D_801EB468;
    ret          = ((u32)D_801EB464 >= 0xDC);
    D_801EB45C.x = 0;
    D_801EB45C.y = y;
    D_801EB45C.h = 240;
    D_801EB468   = size;
    DecDCTReset(1);
    DecDCTin(((u_long**)&D_801EB44C)[D_801EB458], 1);
    DecDCTout(D_801EB444, 2880);
    next       = (D_801EB458 == 0);
    next_buf   = ((u_long**)&D_801EB44C)[next];
    D_801EB458 = next;
    DecDCTvlc(vlc_data, next_buf);
    StFreeRing(vlc_data);
    if (((u32)(D_801EB464 - 0xAD)) >= 0x52) {
        Logo_WaitFrame();
    }
    VSync(2);
    Logo_FlipDisplay();
    return ret;
}

/* Unlifted post-main companions; signatures follow their call sites. */

/* func_801CEBFC */
MATCH void Logo_StopStream(void) { /* func_801CEBFC */
    Logo_FadeOutAudio();
    StUnSetRing();
    CdReady(0, 0);
    CdGetSector((void*)D_801EB44C, 0x200);
    D_801EB440 = 0x80;
    while (CdControlB(CdlSetmode, &D_801EB440, 0) == 0) {
    }
    while (CdControlB(CdlPause, 0, 0) == 0) {
    }
    DecDCToutCallback(0);
}

/* func_801CEC88 */
MATCH void Logo_WaitFrame(void) { /* func_801CEC88 */
    while (D_801EB46C != 0) {
    }
}

/* func_801CECA4 */
MATCH void Logo_DecodeSlice(void) { /* func_801CECA4 */
    if (D_801EB678 != 0) {
        StCdInterrupt();
        D_801EB678 = 0;
    }
    LoadImage(&D_801EB45C, D_801EB444);
    D_801EB45C.x += 0x18;
    if (D_801EB45C.x < 0x1E0) {
        DecDCTout(D_801EB444, 2880);
        D_801EB46C = 1;
    } else {
        D_801EB46C = 0;
    }
}

/* func_801CED48 */
MATCH s32 Logo_FadeInAudio(void) { /* func_801CED48 */
    int level;

    for (level = 0; level < 129; level += 2) {
        s_LogoCDVolume[0] = level;
        s_LogoCDVolume[1] = 0;
        s_LogoCDVolume[2] = level;
        s_LogoCDVolume[3] = 0;
        CdMix((CdlATV*)s_LogoCDVolume);
    }
}

/* func_801CEDA4 */
MATCH void Logo_FadeOutAudio(void) { /* func_801CEDA4 */
    int level;

    for (level = 0x80; level >= 0; level -= 2) {
        s_LogoCDVolume[0] = level;
        s_LogoCDVolume[1] = 0;
        s_LogoCDVolume[2] = level;
        s_LogoCDVolume[3] = 0;
        CdMix((CdlATV*)s_LogoCDVolume);
    }
}

/* func_801CEDFC */
MATCH void Logo_Main(void) { /* func_801CEDFC */
    volatile u8 scratch[24];
    u_long      pad_state;
    int         stream_finished;

    (void)scratch;
    __main();
    CdInit();
    Logo_Init(LOGO_WORK_BASE, D_801D8BB0);
    do {
        pad_state = PadRead(0);
        if ((pad_state & PADstart) != 0) {
            break;
        }
        stream_finished = Logo_DrawFrame();
    } while (stream_finished == 0);
    Logo_StopStream();
    StopCallback();
    PadStop();
    SetDispMask(0);
}
