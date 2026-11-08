#include "logo/logo.h"
#include "gfx/prim.h"

/* func_801CE760 */
MATCH void Logo_Init(s32 work_base, u_long disc_lba) { /* func_801CE760 */
    volatile u8 scratch[0x30];

    (void)scratch;
    D_801EB448 = work_base + 0x2D00;
    D_801EB444 = (u_long*)work_base;
    D_801EB454 = 0;
    D_801EB44C = work_base + 0xA500;
    D_801EB450 = work_base + 0x10480;
    CdReadSync(0, 0);
    PadInit(0);
    Logo_InitDisplay();
    Logo_StartStream(disc_lba);
    Logo_FadeInAudio();
}

/* func_801CE7F4 */
MATCH void Logo_InitDisplay(void) { /* func_801CE7F4 */
    DISPENV* disp;
    RECT     clip;
    s32      height;

    ResetGraph(0);
    SetDispMask(0);
    SetVideoMode(MODE_NTSC);
    height = SCREEN_HEIGHT;
    disp   = D_801EB480;
    SetDefDispEnv(disp, 0, 0, SCREEN_WIDTH, height);
    disp++;
    SetDefDispEnv(disp, 0, SCREEN_HEIGHT, SCREEN_WIDTH, height);
    D_801EB4A5 = 1;
    D_801EB491 = 1;
    clip.w     = 960;
    D_801EB4A8 = 0;
    clip.x     = 0;
    clip.y     = 0;
    clip.h     = 480;
    ClearImage(&clip, 0, 0, 0);
    DrawSync(0);
    VSync(0);
    PutDispEnv(disp);
    SetDispMask(1);
}

/* func_801CE8DC */
MATCH void Logo_FlipDisplay(void) { /* func_801CE8DC */
    PutDispEnv(&D_801EB480[D_801EB4A8]);
    D_801EB4A8 ^= 1;
}
