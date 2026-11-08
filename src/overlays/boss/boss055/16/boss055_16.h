#ifndef OVERLAY_BOSS_BOSS055_16_H
#define OVERLAY_BOSS_BOSS055_16_H

/* The boss/boss055/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyMember record in this image. */
#define g_Task ((PartyMember*)g_Task)

extern s8 D_80146875;
#include "overlays/battle/battle.h"

/* The ten script ids a phase starts, picked by the word at D_801463BE. */
typedef union Boss055Scripts {
    s8 id[10];
    u8 byte[10];
} Boss055Scripts;

ASSERT_SIZE(Boss055Scripts, 10);

extern Boss055Scripts D_800C1804;
extern Boss055Scripts D_800C1810;
extern Boss055Scripts D_800C181C;
extern Callback       D_800C184C[];
extern Callback       D_800C356C[];
extern Callback       D_800C359C[];
extern Callback       D_800C35A4[];
extern Callback       D_800C35AC[];
extern Callback       D_800C35B4[];
extern Callback       D_800C35CC[];
extern Callback       D_800C35EC[];
extern Callback       D_800C35F8[];
extern u16            D_801463BE;
/* D_801EB630 */

void func_800C238C(u8 arg0, u8 arg1);
void func_800C2780(void);
void func_800C27E8(void);
void func_800C28E0(void);
void func_800C2948(void);
void func_800C2A40(void);
void func_800C2AA8(void);
void func_800C2BA0(void);
void func_800C2C78(void);
void func_800C2D2C(void);
void func_800C2E04(void);
void func_800C2ECC(void);
void func_800C2FA4(void);
void func_800C3284(void);

void func_800C227C(void);
void func_800C2340(u8 arg0, u8 index, u8 value);

extern u8       D_80146375;
extern u16      D_801463C0;
extern u8       D_801CA718[][20];
extern Callback D_800C35D8[];

#endif
