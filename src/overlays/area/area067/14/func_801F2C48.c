#include "area067_14.h"

/* Anchor the message banner between the first two actor rows and start message 0x14. */
MATCH void func_801F2C48(void) {
    AreaRippleQuad* quad;
    s32             pos[3];
    DVECTOR         screen;
    u8              scratch[32];

    quad       = (AreaRippleQuad*)&SELF(Actor)->vx;
    D_801F53A0 = TO_COORD(28);
    D_801F53A4 = TO_COORD(24);
    Camera_SetMatrix(scratch);

    pos[0] = g_Actors[0].pos.x.fixed;
    pos[1] = g_Actors[0].pos.y.fixed;
    pos[2] = g_Actors[0].pos.z.fixed;
    Camera_ProjectPoint(pos, &screen);
    quad->x = screen.vx;
    quad->y = screen.vy;

    pos[0] = g_Actors[1].pos.x.fixed;
    pos[1] = g_Actors[1].pos.y.fixed;
    pos[2] = g_Actors[1].pos.z.fixed;
    Camera_ProjectPoint(pos, &screen);
    quad->x += screen.vx;
    quad->y += screen.vy;
    quad->radius = 0;
    quad->height = 0;
    quad->x      = (s16)quad->x >> 1;
    quad->y      = (s16)quad->y >> 1;

    MESSAGE_START_WAIT(MSG_AREA067_020);
    SELF(Actor)->timer = 50;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
}
