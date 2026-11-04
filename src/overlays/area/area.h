#ifndef OVERLAY_AREA_AREA_H
#define OVERLAY_AREA_AREA_H

/* The area group's declarations: the symbols two or more area images read or
 * call. A world header includes this file; an image header includes its world
 * header. */

#include "game.h"
#include "sys/exe.h"
#include "sys/scene.h"
#include "gfx/vram.h"
#include "area/fishing.h"
#include "work/actor.h"
#include "menu/inventory.h"
#include "menu/panel.h"
#include "menu/party.h"
#include "slus/facing.h"
#include "scenario/runtime.h"
#include <abs.h>

/* One panel marker row selected by a controller mask: the mask, the panel
 * step it selects and an unused byte. */
typedef struct WorldMapMarker {
    u16           mask;
    /* 0x02 */ u8 step;
    u8            unk_03;
} WorldMapMarker;

ASSERT_SIZE(WorldMapMarker, 4);

/* One 4-byte map point: the x and y bytes, then the class byte and a pad byte. */
typedef struct WorldMapPoint {
    u8 x;      /* 0x00 */
    u8 y;      /* 0x01 */
    u8 unk_02; /* 0x02 */
    u8 unk_03; /* 0x03 */
} WorldMapPoint;

ASSERT_SIZE(WorldMapPoint, 4);

extern u8       D_80143F06;
extern u16      D_801448EE;
extern u8       D_80146867;
/* D_801D4285 */
extern u8       g_MasterStep;
void            func_801F2C14(void);
void            func_801F2C18(void);
void            func_801F2C30(void);
/* func_801F2C38 */
void            Fish_LocationMessage(void);
void            func_801F2C48(void);
void            func_801F2C5C(void);
void            func_801F2C88(void);
void            func_801F2C8C(void);
void            func_801F2D18(void);
void            func_801F2D3C(void);
extern u8       D_801F2DD4[];
void            func_801F2E1C(void);
void            func_801F2E80(s32 entry_x);
void            func_801F2ED8(void);
void            func_801F2EEC(void);
void            func_801F2F24(void);
void            func_801F309C(void);
void            func_801F3120(void);
void            func_801F314C(void);
void            func_801F31EC(void);
void            func_801F3244(void);
void            func_801F3264(void);
/* func_801F3400 */
void            Actor_CenterOnScreen(void);
/* func_801F3360 */
void            Actor_ShrinkAndFinish(void);
void            func_801F33A8(void);
void            func_801F341C(void);
extern u8       D_801F3424[];
void            func_801F34A0(void);
void            func_801F34E0(void);
void            func_801F358C(void);
void            func_801F35E0(void);
void            func_801F35FC(void);
void            func_801F3690(void);
void            func_801F36A4(void);
void            func_801F3750(void);
void            func_801F385C(void);
void            func_801F38DC(void);
void            func_801F390C(s32 x, s32 y, u32 sprite_id);
void            func_801F39BC(void);
void            func_801F39D8(s32 x, s32 y, u32 sprite_id);
void            func_801F3A64(void);
void            func_801F3A78(void);
void            func_801F3D28(void);
s16             func_801F4158(DVECTOR* a, DVECTOR* b, DVECTOR* c);
void            func_801F4178(void);
void            func_801F41D8(void);
void            func_801F4534(void);
void            func_801F455C(void);
void            func_801F45CC(void);
void            func_801F4768(void);
extern u8       D_801F4624[];
extern Callback D_801F4F64[];
extern u8       D_801F5364[];
extern Callback D_801F5804[];

extern u8 D_80147ACF;

void Area_DrawHud(s16 x, s16 y);

#endif
